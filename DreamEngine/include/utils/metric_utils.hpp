#include <windows.h>
// float GetTickCount()
// {
//     auto now = std::chrono::system_clock::now();

//     // Convert the current time to time since epoch
//     auto duration = now.time_since_epoch();

//     // Convert duration to milliseconds
//     return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    
// }


unsigned int get_FPS()
{
    static unsigned int fps = 0;
    static unsigned int last_fps = 0;
    static DWORD last_time = 0;

    DWORD current_time = GetTickCount();
    ++fps;
    if( current_time - last_time > 1.0f )
    {
        last_fps = fps;
        fps = 0;
        last_time = current_time;
    }
    return last_fps;
} 