"use strict"
// const addon = require('bindings')('hello_world');



const data1 = [
        50000, 500, 1000,
            1,500,
            1,500,
            1,1000,
            2,1500,
        20000, 500, 1000,
            3,1000,
            1,1500,
            1,2000,
            4,2500,
        20000, 500, 1000,
            1,1000,
            1,2500,
            1,3000,
            1,2000,
        10000, 500, 1000,
            1,4000,
            1,4500,
            1,5000,
            1, 5000,
        50000, 500, 1000,
            1,4000,
            1,4500,
            1,5000,
            1,5000

];

const data2 = [
    50000, 500, 1000,
    1, 500,
    1, 500,
    1, 1000,
    2, 1500,
20000, 500, 1000,
    3, 1000,
    1, 1500,
    1, 2000,
    4, 2500,
20000, 500, 1000,
    1, 1000,
    1, 2500,
    1, 3000,
    1, 2000,
20000, 500, 1000,
    1, 4000,
    1, 4500,
    1, 5000,
    1, 5000,
50000, 500, 1000,
    1, 4000,
    1, 4500,
    1, 5000,
    1, 5000
];

const arrByArray1 = new Uint32Array( data1 );
const arrByArray2 = new Uint32Array( data2 );
const addon = require('./build/release/hello_world');
const startTime = Date.now();
const str = addon.sayHi( arrByArray1, arrByArray2 );
const endTime = Date.now();

console.log( str );
console.log( "Elapsed Time :" + ( endTime - startTime ) );



