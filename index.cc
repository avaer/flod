#include <node.h>
#include "flod.h"
#include <iostream>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;
using v8::Array;
using v8::ArrayBuffer;
using v8::Float32Array;
using v8::Uint32Array;
 
void Flod(const FunctionCallbackInfo<Value>& args) {
  Local<String> bufferString = String::NewFromUtf8(args.GetIsolate(), "buffer");
  Local<String> byteOffsetString = String::NewFromUtf8(args.GetIsolate(), "byteOffset");

  Local<ArrayBuffer> etherBuffer = Local<ArrayBuffer>::Cast(args[0]->ToObject()->Get(bufferString));
  unsigned int etherByteOffset = args[0]->ToObject()->Get(byteOffsetString)->Uint32Value();
  Local<Array> shiftArg = Local<Array>::Cast(args[1]);
  Local<ArrayBuffer> peekBuffer = Local<ArrayBuffer>::Cast(args[2]->ToObject()->Get(bufferString));
  unsigned int peekByteOffset = args[2]->ToObject()->Get(byteOffsetString)->Uint32Value();

  float *ether = (float *)((char *)etherBuffer->GetContents().Data() + etherByteOffset);
  int shift[3] = {
    shiftArg->Get(0)->Int32Value(),
    shiftArg->Get(1)->Int32Value(),
    shiftArg->Get(2)->Int32Value()
  };
  unsigned char *peeks = (unsigned char *)((char *)peekBuffer->GetContents().Data() + peekByteOffset);

  // std::cout << "got init " << potential[99] << ":" << potential[100] << ":" << shift[0] << ":" << shift[1] << ":" << shift[2] << "\n";

  flod(ether, shift, peeks);

  /* Local<Object> result = Object::New(args.GetIsolate());
  result->Set(positionsString, Float32Array::New(positionsBuffer, positionsByteOffset, positionIndex));
  result->Set(indicesString, Uint32Array::New(facesBuffer, facesByteOffset, faceIndex));
  args.GetReturnValue().Set(result); */
}

void InitAll(Local<Object> exports, Local<Object> module) {
  init();

  NODE_SET_METHOD(module, "exports", Flod);
}

NODE_MODULE(addon, InitAll)
