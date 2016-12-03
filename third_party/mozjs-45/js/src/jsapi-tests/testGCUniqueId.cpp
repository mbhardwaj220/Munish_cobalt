/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
* vim: set ts=8 sts=4 et sw=4 tw=99:
*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "gc/GCInternals.h"
#include "gc/Zone.h"

#include "jsapi-tests/tests.h"

static void
MinimizeHeap(JSRuntime* rt)
{
    // The second collection is to force us to wait for the background
    // sweeping that the first GC started to finish.
    JS_GC(rt);
    JS_GC(rt);
    js::gc::AutoFinishGC finish(rt);
}

BEGIN_TEST(testGCUID)
{
#ifdef JS_GC_ZEAL
    AutoLeaveZeal nozeal(cx);
#endif /* JS_GC_ZEAL */

    uint64_t uid = 0;
    uint64_t tmp = 0;

    // Ensure the heap is as minimal as it can get.
    MinimizeHeap(rt);

    JS::RootedObject obj(cx, JS_NewPlainObject(cx));
    uintptr_t nurseryAddr = uintptr_t(obj.get());
    CHECK(obj);
    CHECK(js::gc::IsInsideNursery(obj));

    // Do not start with an ID.
    CHECK(!obj->zone()->hasUniqueId(obj));

    // Ensure we can get a new UID.
    CHECK(obj->zone()->getUniqueId(obj, &uid));
    CHECK(uid > js::gc::LargestTaggedNullCellPointer);

    // We should now have an id.
    CHECK(obj->zone()->hasUniqueId(obj));

    // Calling again should get us the same thing.
    CHECK(obj->zone()->getUniqueId(obj, &tmp));
    CHECK(uid == tmp);

    // Tenure the thing and check that the UID moved with it.
    MinimizeHeap(rt);
    uintptr_t tenuredAddr = uintptr_t(obj.get());
    CHECK(tenuredAddr != nurseryAddr);
    CHECK(!js::gc::IsInsideNursery(obj));
    CHECK(obj->zone()->hasUniqueId(obj));
    CHECK(obj->zone()->getUniqueId(obj, &tmp));
    CHECK(uid == tmp);

    // Allocate a new nursery thing in the same location and check that we
    // removed the prior uid that was attached to the location.
    obj = JS_NewPlainObject(cx);
    CHECK(obj);
    CHECK(uintptr_t(obj.get()) == nurseryAddr);
    CHECK(!obj->zone()->hasUniqueId(obj));

    // Try to get another tenured object in the same location and check that
    // the uid was removed correctly.
    obj = nullptr;
    MinimizeHeap(rt);
    obj = JS_NewPlainObject(cx);
    MinimizeHeap(rt);
    CHECK(uintptr_t(obj.get()) == tenuredAddr);
    CHECK(!obj->zone()->hasUniqueId(obj));
    CHECK(obj->zone()->getUniqueId(obj, &tmp));
    CHECK(uid != tmp);
    uid = tmp;

    // Allocate a few arenas worth of objects to ensure we get some compaction.
    const static size_t N = 2049;
    using ObjectVector = js::TraceableVector<JSObject*>;
    JS::Rooted<ObjectVector> vec(cx, ObjectVector(cx));
    for (size_t i = 0; i < N; ++i) {
        obj = JS_NewPlainObject(cx);
        CHECK(obj);
        CHECK(vec.append(obj));
    }

    // Transfer our vector to tenured if it isn't there already.
    MinimizeHeap(rt);

    // Tear holes in the heap by unrooting the even objects and collecting.
    JS::Rooted<ObjectVector> vec2(cx, ObjectVector(cx));
    for (size_t i = 0; i < N; ++i) {
        if (i % 2 == 1)
            vec2.append(vec[i]);
    }
    vec.clear();
    MinimizeHeap(rt);

    // Grab the last object in the vector as our object of interest.
    obj = vec2.back();
    CHECK(obj);
    tenuredAddr = uintptr_t(obj.get());
    CHECK(obj->zone()->getUniqueId(obj, &uid));

    // Force a compaction to move the object and check that the uid moved to
    // the new tenured heap location.
    JS::PrepareForFullGC(rt);
    JS::GCForReason(rt, GC_SHRINK, JS::gcreason::API);
    MinimizeHeap(rt);
    CHECK(uintptr_t(obj.get()) != tenuredAddr);
    CHECK(obj->zone()->hasUniqueId(obj));
    CHECK(obj->zone()->getUniqueId(obj, &tmp));
    CHECK(uid == tmp);

    return true;
}
END_TEST(testGCUID)
