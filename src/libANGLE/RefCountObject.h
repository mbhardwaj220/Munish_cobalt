//
// Copyright (c) 2002-2010 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// RefCountObject.h: Defines the gl::RefCountObject base class that provides
// lifecycle support for GL objects using the traditional BindObject scheme, but
// that need to be reference counted for correct cross-context deletion.
// (Concretely, textures, buffers and renderbuffers.)

#ifndef LIBANGLE_REFCOUNTOBJECT_H_
#define LIBANGLE_REFCOUNTOBJECT_H_

#include "common/debug.h"

#include "angle_gl.h"

#include <cstddef>

namespace gl
{
class Context;
}

class RefCountObjectNoID : angle::NonCopyable
{
  public:
    RefCountObjectNoID() : mRefCount(0) {}

    void addRef() const { ++mRefCount; }

    void release() const
    {
        ASSERT(mRefCount > 0);

        if (--mRefCount == 0)
        {
            delete this;
        }
    }

    // A specialized release method for objects which need a destroy context.
    void release(const gl::Context *context)
    {
        ASSERT(mRefCount > 0);
        if (--mRefCount == 0)
        {
            destroy(context);
            delete this;
        }
    }

    size_t getRefCount() const { return mRefCount; }

  protected:
    virtual ~RefCountObjectNoID() { ASSERT(mRefCount == 0); }
    virtual void destroy(const gl::Context *context) {}

  private:
    mutable std::size_t mRefCount;
};

class RefCountObject : public RefCountObjectNoID
{
  public:
    explicit RefCountObject(GLuint id) : mId(id) {}

    GLuint id() const { return mId; }

  protected:
    ~RefCountObject() override {}

  private:
    GLuint mId;
};

template <class ObjectType>
class BindingPointer
{
  public:
    BindingPointer()
        : mObject(nullptr)
    {
    }

    BindingPointer(const BindingPointer<ObjectType> &other)
        : mObject(nullptr)
    {
        set(other.mObject);
    }

    void operator=(const BindingPointer<ObjectType> &other)
    {
        set(other.mObject);
    }

    virtual ~BindingPointer()
    {
        // Objects have to be released before the resource manager is destroyed, so they must be explicitly cleaned up.
        ASSERT(mObject == nullptr);
    }

    virtual void set(ObjectType *newObject)
    {
        // addRef first in case newObject == mObject and this is the last reference to it.
        if (newObject != nullptr) reinterpret_cast<const RefCountObject*>(newObject)->addRef();
        if (mObject != nullptr) reinterpret_cast<const RefCountObject*>(mObject)->release();
        mObject = newObject;
    }

    ObjectType *get() const { return mObject; }
    ObjectType *operator->() const { return mObject; }

    GLuint id() const { return (mObject != nullptr) ? mObject->id() : 0; }

    bool operator==(const BindingPointer<ObjectType> &other) const
    {
        return mObject == other.mObject;
    }

    bool operator!=(const BindingPointer<ObjectType> &other) const { return !(*this == other); }

  private:
    ObjectType *mObject;
};

template <class ObjectType>
class OffsetBindingPointer : public BindingPointer<ObjectType>
{
  public:
    OffsetBindingPointer() : mOffset(0), mSize(0) { }

    void set(ObjectType *newObject) override
    {
        BindingPointer<ObjectType>::set(newObject);
        mOffset = 0;
        mSize = 0;
    }

    void set(ObjectType *newObject, GLintptr offset, GLsizeiptr size)
    {
        BindingPointer<ObjectType>::set(newObject);
        mOffset = offset;
        mSize = size;
    }

    GLintptr getOffset() const { return mOffset; }
    GLsizeiptr getSize() const { return mSize; }

    bool operator==(const OffsetBindingPointer<ObjectType> &other) const
    {
        return this->get() == other.get() && mOffset == other.mOffset && mSize == other.mSize;
    }

    bool operator!=(const OffsetBindingPointer<ObjectType> &other) const
    {
        return !(*this == other);
    }

  private:
    GLintptr mOffset;
    GLsizeiptr mSize;
};

#endif   // LIBANGLE_REFCOUNTOBJECT_H_
