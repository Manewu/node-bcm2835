#include <nan.h>
extern "C" {
#include <unistd.h>
#include "bcm2835.h"
}

void SetGPIO(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber() || !info[1]->IsString()) {
        Nan::ThrowTypeError("First argument should be number (GPIO), second string (in or out)");
        return;
    }

    if (std::string(*Nan::Utf8String(info[1]->ToString())) == "out")
        bcm2835_gpio_fsel(info[0]->NumberValue(), BCM2835_GPIO_FSEL_OUTP);
    else if (std::string(*Nan::Utf8String(info[1]->ToString())) == "in")
        bcm2835_gpio_fsel(info[0]->NumberValue(), BCM2835_GPIO_FSEL_INPT);

    info.GetReturnValue().Set(0);
#else
#endif
}

void WriteGPIO(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be number (GPIO), second number (0 or 1) or bool");
        return;
    }

	bcm2835_gpio_write(info[0]->NumberValue(), info[1]->NumberValue());

    info.GetReturnValue().Set(0);
#else
#endif
}

void ReadGPIO(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be number (GPIO)");
        return;
    }

	uint8_t value = bcm2835_gpio_lev(info[0]->NumberValue());

    info.GetReturnValue().Set(value);
#else
#endif
}

void InitIO(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (geteuid() != 0) {
        Nan::ThrowError("You must be root to access IO");
        return;
    }

    if (!bcm2835_init()) Nan::ThrowError("Could not initialize IO");
    else
    {
        bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
        info.GetReturnValue().Set(1);
    }
#else
#endif
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("initIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(InitIO)->GetFunction());
    exports->Set(Nan::New("setGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(SetGPIO)->GetFunction());
    exports->Set(Nan::New("writeGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(WriteGPIO)->GetFunction());
    exports->Set(Nan::New("readGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(ReadGPIO)->GetFunction());
}

NODE_MODULE(addon, Init)
