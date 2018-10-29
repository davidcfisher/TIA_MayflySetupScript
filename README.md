# TIA_MayflySetupScript
Ensure VSCode, PlatformIO and GIT are set up correctly for connection to Mayfly
## Setup steps
1. Download and install **Visual Studio Code** (VSCode) (note: NOT *Visual Studio IDE*)
    1. https://visualstudio.microsoft.com
1. Install the **PlatformIO IDE** in VSCode
    1. "Reload" PlatformIO IDE to activate it.  It may take several minutes to be activated and loaded - watch status in lower right corner of window - status in the terminal window.  VSCode may need to be restarted (multiple times).
1. Update or download and install **GIT**
    1. https://git-scm.com/download/win
    1. Initialize GIT in VSCode, using the PowerShell terminal:
        1. PS C:\yourGitLocation> git init
        1. PS C:\yourGitLocation> git config --global user.email "your@email.com"
        1. PS C:\yourGitLocation> git config --global user.name "Your Name"

