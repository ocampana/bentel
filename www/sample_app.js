/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

const TEMP_UPDATE_INTVL_MS = 2 * 2718;
const AP_UPDATE_INTVL_MS = 3 * 3141;

const SCALE_PREF_KEY = "scalePref";
const DEFAULT_SCALE_PREF = 'K';

let scalePref = DEFAULT_SCALE_PREF;
let tempK = 0.0;

const tempValElem = document.getElementById("tempValue");
const tempScaleElem = document.getElementById("tempScale");
const scaleBtnK = document.getElementById("scaleK");
const scaleBtnC = document.getElementById("scaleC");
const scaleBtnF = document.getElementById("scaleF");
const scale2Btn = {
    "K": scaleBtnK,
    "C": scaleBtnC,
    "F": scaleBtnF,
};

const ledBoxElem = document.getElementById("ledBox");
const ledStateElem = document.getElementById("ledState");
const ledBtnOn = document.getElementById("ledBtnOn");
const ledBtnOff = document.getElementById("ledBtnOff");
const ledBtnToggle = document.getElementById("ledBtnToggle");

const ssidTextElem = document.getElementById("ssid_text");
const rssiTextElem = document.getElementById("rssi_text");
const ssidElem = document.getElementById("ssid");
const rssiElem = document.getElementById("rssi");
const ssElem = document.getElementById("ss_pct");

const toastElem = document.getElementById("toast");
const errMsgElem = document.getElementById("errMsg");

const TOAST_INTVL_MS = 5000;
let toastTimeout = -1;

function toast(err) {
    if (toastTimeout != -1) {
        clearTimeout(toastTimeout);
    }
    errMsgElem.textContent = err.message;
    toastElem.style.display = "block";
    toastTimeout = setTimeout(() => {
        toastElem.style.display = "none";
    }, TOAST_INTVL_MS);
}

async function getResp(url) {
    let response = await fetch(url);
    if (!response.ok)
        throw new Error(url + " response status: " + response.status);
    return response;
}

function renderTemp(tmpK, scale) {
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
        throw new Error("temperature scale: " + scale);
    }
    tempValElem.textContent = tempVal.toString();
    tempScaleElem.textContent = scale;
}

async function updateTemp() {
    if (document.visibilityState === "hidden") {
        return;
    }

    try {
        let response = await getResp("/temp");
        let body = await response.text();
        let tempK_q18_14 = parseInt(body);
        if (tempK_q18_14 == NaN)
            throw new Error("/temp response body: " + body);
        tempK = tempK_q18_14 / 16384.0;
        renderTemp(tempK, scalePref);
    }
    catch (ex) {
        toast(ex);
    }
}

function updateScalePref(pref) {
    scalePref = pref;
    localStorage.setItem(SCALE_PREF_KEY, pref);
}

function doScale(scale) {
    if (scale == scalePref)
        return;

    let btn = scale2Btn[scale];
    let prevBtn = scale2Btn[scalePref];
    prevBtn.classList.replace("scaleActive", "btnPlain");
    btn.classList.replace("btnPlain", "scaleActive");
    updateScalePref(scale);

    try {
        renderTemp(tempK, scalePref);
    }
    catch (err) {
        toast(err);
    }
}

function doScaleK() {
    doScale("K");
}

function doScaleC() {
    doScale("C");
}

function doScaleF() {
    doScale("F");
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
        toast(ex);
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
    if (document.visibilityState === "hidden") {
        return;
    }

    let data = null;
    try {
        let response = await getResp("/ap");
        data = await response.json();
    }
    catch (ex) {
        toast(ex);
        return;
    }

    ssidElem.textContent = data.ssid;
    ssidTextElem.style.display = "inline";
    if (data.have_rssi) {
        rssiElem.textContent = data.rssi.toString();
        ssElem.textContent
            = Math.min(Math.max(2 * (100 + data.rssi), 0), 100).toString();
        rssiTextElem.style.display = "inline";
    }
}

async function updateOnVisible() {
    if (document.visibilityState === "hidden") {
        return;
    }

    await updateTemp();
    await updateAP();
}

async function init() {
    await updateTemp();
    let scale = localStorage.getItem(SCALE_PREF_KEY);
    if (scale == null) {
        scale = DEFAULT_SCALE_PREF;
    }
    doScale(scale);
    await updateLed();
    await updateAP();

    document.addEventListener("visibilitychange", updateOnVisible);

    scaleBtnK.addEventListener("click", doScaleK);
    scaleBtnC.addEventListener("click", doScaleC);
    scaleBtnF.addEventListener("click", doScaleF);

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
