/**
 * Created by Uwe on 10.11.2015.
 */

var piIO = require('./build/Release/bcm2835-io');

console.log(piIO.initIO());
console.log(piIO.setGPIO(12, 'out'));
console.log(piIO.writeGPIO(12, false));
console.log("In value: ", piIO.readGPIO(12));
console.log("SetGPIO_pud: ", piIO.setGPIO_pud(21, 2));
console.log("beginI2c: ", piIO.beginI2c());
console.log("writeI2c: ", piIO.writeI2c(new Buffer([10, 20]), 2));
