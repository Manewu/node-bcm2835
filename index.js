/**
 * Created by Uwe on 10.11.2015.
 */

var piIO = require('./build/Release/bcm2835-io');

console.log(piIO.initIO());
console.log(piIO.setGPIO(12, 'out'));
console.log(piIO.writeGPIO(12, false));
console.log("In value: ", piIO.readGPIO(12));

