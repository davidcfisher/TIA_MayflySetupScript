# TIA_MayflySetupScript
Ensure VSCode, PlatformIO and GIT are set up correctly for connection to Mayfly
## Setup steps
1. Download and install **Visual Studio Code** (VSCode) (note: NOT *Visual Studio IDE*)
    1. https://visualstudio.microsoft.com
1. Install the **PlatformIO IDE** Extension in VSCode
    1. "Reload" PlatformIO IDE to activate it.  It may take several minutes to be activated and loaded - watch status in lower left corner of window - and status in the terminal window.  VSCode may need to be restarted (multiple times).
1. Update or download and install **Git**
    1. https://git-scm.com/download/win
    1. Add Git Repository to VSCode, using Command Pallette (View/Command Pallette)
        1. Git: Initialize Repository 
    1. Customize Git in VSCode, using the PowerShell terminal (View/Terminal):
        1. PS C:\yourGitLocation> git config --global user.email "your@email.com"
        1. PS C:\yourGitLocation> git config --global user.name "Your Name"
1. Clone repository from GitHub onto local computer
    1. Using Command Pallette
        1. Git: Clone
        1. Repository URL: https://github.com/davidcfisher/TIA_MayflySetupScript (for example)
        1. Select folder: location for code on your local machine