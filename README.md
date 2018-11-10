# TIA_MayflySetupScript
Ensure VSCode, PlatformIO and GIT are set up correctly for connection to Mayfly
## Setup steps
1. Determine location of files on local machine
    1. Example: C:/data/Mayfly
1. Download and install **Visual Studio Code** (VSCode) (note: NOT *Visual Studio IDE*)
    1. https://visualstudio.microsoft.com
    1. **Git**
        1. If Git is not installed on your machine (or is downlevel), VSCode will allow for installation or update.
            1. During setup: Choosing the default editor used by Git
                1. Use Visual Studio Code as Git's default editor
1. Install the **PlatformIO IDE** Extension in VSCode
    1. Reference: http://docs.platformio.org/en/latest/ide/vscode.html#ide-vscode
    1. "Reload" PlatformIO IDE to activate it, if needed.  It may take several minutes to be activated and loaded - watch status in lower left corner of window - and status in the terminal window.  VSCode may need to be restarted (multiple times).
1. Initialize **Git**
    1. Initialize Git Repository in VSCode, using Command Pallette (View/Command Pallette)
        1. Git: Initialize Repository 
    1. Customize Git in VSCode, using the terminal (View/Terminal):
        1. PS C:\yourGitLocation> git config --global user.email "your@email.com"
        1. PS C:\yourGitLocation> git config --global user.name "Your Name"
1. Install **Mayfly** libraries, using the terminal
    1. PS C:\yourGitLocation> pio lib -g install https://github.com/EnviroDIY/Libraries.git#platformio
    1. Note: to get the latest updates:
        1. PS C:\yourGitLocation> pio lib -g update
    1. Reference: https://github.com/EnviroDIY/Libraries
1. Clone repository from GitHub onto local computer
    1. Using Command Pallette
        1. Git: Clone
        1. Repository URL: https://github.com/davidcfisher/TIA_MayflySetupScript (for example)
        1. Select folder: (C:/data/Mayfly, for example)
1. Update platformio.ini as needed
    1. Change *upload_port = COMX* 

