// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef NATIVE_MATE_PROMISE_H_
#define NATIVE_MATE_PROMISE_H_

#include "native_mate/converter.h"
#include "native_mate/scoped_persistent.h"

namespace mate {

class Promise {
 public:
  Promise();
  Promise(v8::Isolate* isolate);
  virtual ~Promise();

  static Promise Create(v8::Isolate* isolate);
  static Promise Create();

  v8::Isolate* isolate() const { return isolate_; }
  bool IsEmpty() const { return isolate() == NULL; }

  virtual v8::Local<v8::Promise::Resolver> GetHandle() const;

  template<typename T>
  void Resolve(T* value) {
    GetHandle()->Resolve(mate::ConvertToV8(isolate(), value));
  }

  template<typename T>
  void Reject(T* value) {
    GetHandle()->Reject(mate::ConvertToV8(isolate(), value));
  }

  void RejectWithErrorMessage(const std::string& error);

 protected:
  v8::Isolate* isolate_;

 private:
  scoped_refptr<RefCountedPersistent<v8::Promise::Resolver>> handle_;
};

template<>
struct Converter<Promise> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                    Promise val);
  // TODO(MarshallOfSound): Implement FromV8 to allow promise chaining
  //                        in native land
  // static bool FromV8(v8::Isolate* isolate,
  //                    v8::Local<v8::Value> val,
  //                    Promise* out);
};

}  // namespace mate

#endif  // NATIVE_MATE_PROMISE_H_
