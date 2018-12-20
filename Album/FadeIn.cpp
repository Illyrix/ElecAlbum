#include "stdafx.h"
#include "FadeIn.h"
#include <omp.h>

FadeIn::FadeIn(const LPCTSTR imgs[], UINT len, LPCTSTR defImg)
{
    nLen = 0;
    pImgs = (CImage**)malloc(len * sizeof(CImage*));
    for (UINT i = 0; i < len; i++) {
        LPCTSTR pImgPath = imgs[i];
        CImage* mImg = new CImage();
        mImg->Load(pImgPath);
        if (!mImg->IsNull()) {
            pImgs[nLen++] = mImg;
        }
    }
    nNow = 0;
    fade = 0;
    ASSERT(nLen);
    mCurrImg = pImgs[0];
    tempImg = new CImage();
    tempImg->Load(defImg);
    LoadDLL();
}

CImage* FadeIn::GetNextImg() {
    UINT nTmp = nNow >= nLen - 1 ? 0 : nNow + 1;
    return pImgs[nTmp];
}

CImage* FadeIn::GetPrevImg() {
    return pImgs[nNow];
}

void FadeIn::OnPaint(CWnd* wnd) {
    CRect zcRect;
    wnd->GetClientRect(&zcRect);
    mCurrImg->Draw(wnd->GetDC()->m_hDC, zcRect);
}

void FadeIn::OnFade(CWnd* wnd) {
    if (fade > 0) {
        SYSTEMTIME start, end;
        GetLocalTime(&start);
        auto pPrev = GetPrevImg();
        auto pNext = GetNextImg();
        fnFade(pPrev, pNext, fade, *tempImg);
        mCurrImg = tempImg;
        
        // notify system refresh window
        wnd->SendMessage(WM_PAINT);

        GetLocalTime(&end);
        UINT16 ms = end.wMilliseconds - start.wMilliseconds;
        if (ms >= 0 && ms < 16) {
            Sleep(16 - ms);
        }
    }
}

void FadeIn::LoadDLL() {
    LPCWSTR dllName(_T("../ImageFadeIn.dll"));
    const char* funcName = "fadeIn";
    hDLL = LoadLibrary(dllName);
    ASSERT(hDLL);
    fnFade = (FN)GetProcAddress(hDLL, funcName);
    ASSERT(fnFade);
}

void FadeIn::StartFade(CWnd* wnd) {
    fade = 0;
    while (fade <= 128) {
        OnFade(wnd);
        fade++;
    }
    mCurrImg = pImgs[Next()];
    wnd->SendMessage(WM_PAINT);
}

UINT FadeIn::Next() {
    nNow = nNow >= nLen - 1 ? 0 : nNow + 1;
    return nNow;
}

FadeIn::~FadeIn() {
    FreeLibrary(hDLL);
}