// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "native_mate/promise.h"

namespace mate {

Promise::Promise()
    : isolate_(NULL) {
}

Promise::Promise(v8::Isolate* isolate)
    : isolate_(isolate) {
  handle_ = new RefCountedPersistent<v8::Promise::Resolver>(isolate, v8::Promise::Resolver::New(isolate));
}

Promise::~Promise() {
}

void Promise::RejectWithErrorMessage(const std::string& string) {
  v8::Local<v8::String> error_message =
      v8::String::NewFromUtf8(isolate(), string.c_str());
  v8::Local<v8::Value> error = v8::Exception::Error(error_message);
  GetHandle()->Reject(mate::ConvertToV8(isolate(), error));
}

v8::Local<v8::Promise::Resolver> Promise::GetHandle() const {
  return handle_->NewHandle();
}

v8::Local<v8::Value> Converter<Promise>::ToV8(v8::Isolate* isolate,
                                                  Promise val) {
  return val.GetHandle()->GetPromise();
}

}  // namespace mate
