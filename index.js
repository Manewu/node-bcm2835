/**
 * Created by Uwe on 10.11.2015.
 */

var piIO = require('./build/Release/bcm2835-io');

console.log(piIO.initIO());
console.log(piIO.setGPIO(12, 'out'));
console.log(piIO.writeGPIO(12, !piIO.readGPIO(12)));
console.log("In value: ", piIO.readGPIO(12));
console.log("SetGPIO_pud: ", piIO.setGPIO_pud(21, 2));

console.log("beginI2c: ", piIO.beginI2c());
buf = new Buffer(32*4);

//gesture sensor
console.log("setI2cSlaveAddress: ", piIO.setI2cSlaveAddress(0x39));
console.log("writeI2c: ", piIO.writeI2c(new Buffer([0x80, 0x7F]), 2));

//piIO.writeI2c(new Buffer([0xE7]), 1);   //I2C "address accessing to clear interrupt
console.log("readRegisterI2c: ", piIO.readRegisterRsI2c(0x80, buf, 32*4));
console.log("writeReadRsI2c: ", piIO.writeReadRsI2c(new Buffer([0x80]), 1, buf, 32*4));

console.log("buf: ", buf);
console.log("endI2c: ", piIO.endI2c());
