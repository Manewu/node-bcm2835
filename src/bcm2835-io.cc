#include <nan.h>
extern "C" {
#include <unistd.h>
#include "bcm2835.h"
}

void BeginI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    bcm2835_i2c_begin();
    info.GetReturnValue().Set(0);
#else
#endif
}

void EndI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    bcm2835_i2c_end();
    info.GetReturnValue().Set(0);
#else
#endif
}

void SetI2cSlaveAddress(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be number (I2C Slave address)");
        return;
    }

    bcm2835_i2c_setSlaveAddress(info[0]->NumberValue());

    info.GetReturnValue().Set(0);
#else
#endif
}

void WriteI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!node::Buffer::HasInstance(info[0]) || !info[1]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be Buffer, second byte number (length)");
        return;
    }
    char* buf = (char*) node::Buffer::Data(info[0]->ToObject());
    uint32_t len = info[1]->Uint32Value();

    uint8_t value = bcm2835_i2c_write(buf, len);

    info.GetReturnValue().Set(value);   //bcm2835I2CReasonCodes, 0 = Success
#else
#endif
}

void ReadI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!node::Buffer::HasInstance(info[0]) || !info[1]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be Buffer, second byte #");
        return;
    }
    char* buf = (char*) node::Buffer::Data(info[0]->ToObject());
    uint32_t len = info[1]->Uint32Value();

    //uint8_t bcm2835_i2c_read(char* buf, uint32_t len)
    uint8_t value = bcm2835_i2c_read(buf, len);

    info.GetReturnValue().Set(value);   //bcm2835I2CReasonCodes, 0 = Success
#else
#endif
}

void ReadRegisterRsI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 3) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber() || !node::Buffer::HasInstance(info[1]) || !info[2]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be command/addr., second Buffer, third byte #");
        return;
    }
    char* buf = (char*) node::Buffer::Data(info[1]->ToObject());
    uint32_t len = info[2]->Uint32Value();
    char cmd = info[0]->NumberValue();

    //uint8_t bcm2835_i2c_read_register_rs(char* regaddr, char* buf, uint32_t len)
    uint8_t value = bcm2835_i2c_read_register_rs(&cmd, buf, len);

    info.GetReturnValue().Set(value);   //bcm2835I2CReasonCodes, 0 = Success
#else
#endif
}

void WriteReadRsI2c(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() != 4) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!node::Buffer::HasInstance(info[0]) || !info[1]->IsNumber() ||
            !node::Buffer::HasInstance(info[2]) || !info[3]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be cmds buffer, second byte #, third Buffer, fourth byte #");
        return;
    }
    char* cmds = (char*) node::Buffer::Data(info[0]->ToObject());
    char* buf = (char*) node::Buffer::Data(info[2]->ToObject());
    uint32_t len_cmds = info[1]->Uint32Value();
    uint32_t len_buf = info[3]->Uint32Value();

    //uint8_t bcm2835_i2c_write_read_rs(char* cmds, uint32_t cmds_len, char* buf, uint32_t buf_len)
    uint8_t value = bcm2835_i2c_write_read_rs(cmds, len_cmds, buf, len_buf);

    info.GetReturnValue().Set(value);   //bcm2835I2CReasonCodes, 0 = Success
#else
#endif
}

void SetGPIO_pud(const Nan::FunctionCallbackInfo<v8::Value>& info) {
#ifdef __arm__
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
        Nan::ThrowTypeError("First argument should be number (GPIO), second number (bcm2835PUDControl)");
        return;
    }
    if (info[0]->NumberValue() > 27) {
        Nan::ThrowRangeError("Highest GPIO # = GPIO27");
        return;
    }

    bcm2835_gpio_set_pud(info[0]->NumberValue(), info[1]->NumberValue());

    info.GetReturnValue().Set(0);
#else
#endif
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
    if (info[0]->NumberValue() > 27) {
        Nan::ThrowRangeError("Highest GPIO # = GPIO27");
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
    if (info[0]->NumberValue() > 27) {
        Nan::ThrowRangeError("Highest GPIO # = GPIO27");
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
    if (info[0]->NumberValue() > 27) {
        Nan::ThrowRangeError("Highest GPIO # = GPIO27");
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
    exports->Set(Nan::New("beginI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(BeginI2c)->GetFunction());
    exports->Set(Nan::New("endI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(EndI2c)->GetFunction());
    exports->Set(Nan::New("setI2cSlaveAddress").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(SetI2cSlaveAddress)->GetFunction());
    exports->Set(Nan::New("readI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(ReadI2c)->GetFunction());
    exports->Set(Nan::New("writeI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(WriteI2c)->GetFunction());
    exports->Set(Nan::New("readRegisterRsI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(ReadRegisterRsI2c)->GetFunction());
    exports->Set(Nan::New("writeReadRsI2c").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(WriteReadRsI2c)->GetFunction());
    exports->Set(Nan::New("setGPIO_pud").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(SetGPIO_pud)->GetFunction());
    exports->Set(Nan::New("setGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(SetGPIO)->GetFunction());
    exports->Set(Nan::New("writeGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(WriteGPIO)->GetFunction());
    exports->Set(Nan::New("readGPIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(ReadGPIO)->GetFunction());
    exports->Set(Nan::New("initIO").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(InitIO)->GetFunction());
}

NODE_MODULE(addon, Init)
