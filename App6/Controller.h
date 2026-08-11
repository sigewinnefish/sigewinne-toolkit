#pragma once


namespace Service::NotifyIcon
{
    class Controller
    {
    public:
		Controller() = default;
        void Init();
        void CreatePopupWindow();

    private:
        void AddNotifyIcon();
        void CreateNotifyIconHostWindow();
        void InitMessage();
        void SetCallback();
        HWND m_hwnd{};
        UINT m_NotifyIconCallbackMessage{};
        UINT m_TaskbarCreatedMessage{};
    };


}
