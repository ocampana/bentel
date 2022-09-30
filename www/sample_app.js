/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

const TEMP_UPDATE_INTVL_MS = 2718;
const AP_UPDATE_INTVL_MS = 2 * 3141;

let scale = 'K';
const tempValElem = document.getElementById("tempValue");

const ledBoxElem = document.getElementById("ledBox");
const ledStateElem = document.getElementById("ledState");
const ledBtnOn = document.getElementById("ledBtnOn");
const ledBtnOff = document.getElementById("ledBtnOff");
const ledBtnToggle = document.getElementById("ledBtnToggle");

const ssidTextElem = document.getElementById("ssid_text");
const rssiTextElem = document.getElementById("rssi_text");
const ssidElem = document.getElementById("ssid");
const rssiElem = document.getElementById("rssi");

async function getResp(url) {
    let response = await fetch(url);
    if (!response.ok)
        throw new Error(url + " response status: " + response.status);
    return response;
}

async function updateTemp() {
    let tempVal = 0;
    let body = '';
    try {
        let response = await getResp("/temp");
        body = await response.text();
    }
    catch (ex) {
        /* XXX toast */
        console.log(ex);
        return;
    }

    let tempK_q20_12 = parseInt(body);
    if (tempK_q20_12 == NaN) {
        /* XXX toast */
        console.log("/temp response body: " + body);
        return;
    }
    let tempK = tempK_q20_12 / 4096.0;

    switch (scale) {
    case 'K':
        tempVal = Math.round(tempK);
        break;
    case 'C':
        tempVal = Math.round(tempK - 273.15);
        break;
    case 'F':
        tempVal = Math.round(1.8 * (tempK - 273.15) + 32);
        break;
    default:
        /* XXX toast */
        console.log("/temp scale: " + scale);
        return;
    }
    tempValElem.textContent = tempVal.toString();
}

async function doLed(url) {
    let ledBit = NaN;
    try {
        let response = await getResp(url);
        body = await response.text();
        ledBit = parseInt(body);
        if (ledBit == NaN)
            throw new Error(url + " response body: " + body);
    }
    catch (ex) {
        /* XXX toast */
        console.log(ex);
        return;
    }

    let ledOn = Boolean(ledBit);
    if (ledOn) {
        ledStateElem.textContent = "ON";
        ledBoxElem.classList.remove("ledOff");
        ledBoxElem.classList.add("ledOn");
        return;
    }
    ledStateElem.textContent = "OFF";
    ledBoxElem.classList.remove("ledOn");
    ledBoxElem.classList.add("ledOff");
}

async function updateLed() {
    await doLed("/led");
}

async function ledDoOn() {
    await doLed("/led?op=on");
}

async function ledDoOff() {
    await doLed("/led?op=off");
}

async function ledDoToggle() {
    await doLed("/led?op=toggle");
}

async function updateAP() {
    let data = null;
    try {
        let response = await getResp("/ap");
        data = await response.json();
    }
    catch (ex) {
        /* XXX toast */
        console.log(ex);
        return;
    }

    ssidElem.textContent = data.ssid;
    ssidTextElem.style.display = "inline";
    if (data.have_rssi) {
        rssiElem.textContent = data.rssi.toString();
        rssiTextElem.style.display = "inline";
    }
}

function init() {
    updateTemp();
    updateLed();
    updateAP();

    ledBtnOn.addEventListener("click", ledDoOn);
    ledBtnOff.addEventListener("click", ledDoOff);
    ledBtnToggle.addEventListener("click", ledDoToggle);

    setInterval(updateTemp, TEMP_UPDATE_INTVL_MS);
    setInterval(updateAP, AP_UPDATE_INTVL_MS);
}

if (document.readyState !== "loading") {
    init();
} else {
    document.addEventListener("DOMContentLoaded", init);
}
