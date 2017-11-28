// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_OVERLAY_USER_PREF_STORE_H_
#define BASE_PREFS_OVERLAY_USER_PREF_STORE_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "base/prefs/base_prefs_export.h"
#include "base/prefs/persistent_pref_store.h"
#include "base/prefs/pref_value_map.h"

// PersistentPrefStore that directs all write operations into an in-memory
// PrefValueMap. Read operations are first answered by the PrefValueMap.
// If the PrefValueMap does not contain a value for the requested key,
// the look-up is passed on to an underlying PersistentPrefStore |underlay_|.
class BASE_PREFS_EXPORT OverlayUserPrefStore : public PersistentPrefStore,
                                               public PrefStore::Observer {
 public:
  explicit OverlayUserPrefStore(PersistentPrefStore* underlay);

  // Returns true if a value has been set for the |key| in this
  // OverlayUserPrefStore, i.e. if it potentially overrides a value
  // from the |underlay_|.
  virtual bool IsSetInOverlay(const std::string& key) const;

  // Methods of PrefStore.
  virtual void AddObserver(PrefStore::Observer* observer) override;
  virtual void RemoveObserver(PrefStore::Observer* observer) override;
  virtual size_t NumberOfObservers() const override;
  virtual bool IsInitializationComplete() const override;
  virtual bool GetValue(const std::string& key,
                        const base::Value** result) const override;

  // Methods of PersistentPrefStore.
  virtual bool GetMutableValue(const std::string& key,
                               base::Value** result) override;
  virtual void SetValue(const std::string& key, base::Value* value) override;
  virtual void SetValueSilently(const std::string& key,
                                base::Value* value) override;
  virtual void RemoveValue(const std::string& key) override;
  virtual void MarkNeedsEmptyValue(const std::string& key) override;
  virtual bool ReadOnly() const override;
  virtual PrefReadError GetReadError() const override;
  virtual PrefReadError ReadPrefs() override;
  virtual void ReadPrefsAsync(ReadErrorDelegate* delegate) override;
  virtual void CommitPendingWrite() override;
  virtual void ReportValueChanged(const std::string& key) override;

  // Methods of PrefStore::Observer.
  virtual void OnPrefValueChanged(const std::string& key) override;
  virtual void OnInitializationCompleted(bool succeeded) override;

  void RegisterOverlayPref(const std::string& key);
  void RegisterOverlayPref(const std::string& overlay_key,
                           const std::string& underlay_key);

 protected:
  virtual ~OverlayUserPrefStore();

 private:
  typedef std::map<std::string, std::string> NamesMap;

  const std::string& GetOverlayKey(const std::string& underlay_key) const;
  const std::string& GetUnderlayKey(const std::string& overlay_key) const;

  // Returns true if |key| corresponds to a preference that shall be stored in
  // an in-memory PrefStore that is not persisted to disk.
  bool ShallBeStoredInOverlay(const std::string& key) const;

  ObserverList<PrefStore::Observer, true> observers_;
  PrefValueMap overlay_;
  scoped_refptr<PersistentPrefStore> underlay_;
  NamesMap overlay_to_underlay_names_map_;
  NamesMap underlay_to_overlay_names_map_;

  DISALLOW_COPY_AND_ASSIGN(OverlayUserPrefStore);
};

#endif  // BASE_PREFS_OVERLAY_USER_PREF_STORE_H_
