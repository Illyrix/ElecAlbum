#pragma once
class FadeIn
{
private:
    CImage** pImgs;
    UINT nLen;
    UINT nNow;
    BYTE fade;
    FN fnFade;
    HMODULE hDLL;
    CWnd* wnd;
    CImage* mCurrImg;
    CImage* tempImg;

    void LoadDLL();
public:
    FadeIn(const LPCTSTR[], UINT, LPCTSTR);
    ~FadeIn();
    void OnPaint(CWnd*);
    void OnFade(CWnd*);
    void StartFade(CWnd*);
    UINT Next();

    CImage* GetPrevImg();
    CImage* GetNextImg();
};

