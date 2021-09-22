<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![MIT License][license-shield]][license-url]


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/DauntlessStudio/BedrockUtilities">
  </a>
  <h3 align="center">Utilities For Bedrock Development</h3>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

These utilities are designed to expedite many repetitive and time consuming tasks that you encounter in Bedrock development. Such as:
* Creating new Resource and Behavior packs with manifest.json files
* Adding or removing components/groups/events from entities
* Creating batches of .mcfunction files
* And more

### Built With

* [C++](https://www.cplusplus.com/)



<!-- GETTING STARTED -->
## Getting Started

You can either compile the project from source, or use the installer.

### Installation From Source

1. Clone the repo
   ```sh
   git clone https://github.com/DauntlessStudio/BedrockUtilities.git
   ```
2. Compile  
   Use Compiler of your choice to generate an executeable. On Linux you can use the makefile.
3. Set In Path  
   Windows: %USERPROFILE%/AppData/Local/BedrockUtilities/
   Linux: /usr/bin/
4. (Optional, Windows) Set Environment Variable  
   Run 'Edit the system environment variables'.
   Go to Advanced>Environment Variables>System Variables>Path
   Press 'Edit...' then 'New' and paste in:
   ```sh
   %USERPROFILE%\AppData\Local\BedrockUtilities
   ```

### Using Installer
1. Install  
   Run 'setup.exe'
2. (Optional) Set Environment Variable  
   Run 'Edit the system environment variables'.  
   Go to Advanced>Environment Variables>System Variables>Path  
   Press 'Edit...' then 'New' and paste in:
   ```sh
   %USERPROFILE%\AppData\Local\BedrockUtilities
   ```

<!-- USAGE EXAMPLES -->
## Usage

Using your operating system's terminal (i.e. Command Prompt, Powershell, etc.) set the current directory to your desired resource pack. For example:
```sh
cd %USERPROFILE%/AppData/Local/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang/development_resource_packs/<target-pack>
```
Then set that to be the bedrock utilites resource directory
```sh
bed rdir
```
Do the same with the desired behavior pack using the commands
```sh
cd %USERPROFILE%/AppData/Local/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang/development_behavior_packs/<target-pack>
```
```sh
bed bdir
```


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/DauntlessStudio/BedrockUtilities/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Project Link: [https://github.com/DauntlessStudio/BedrockUtilities](https://github.com/DauntlessStudio/BedrockUtilities)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [JSON For Modern c++](https://github.com/nlohmann/json)
* [Lodepng](https://github.com/lvandeve/lodepng)
* [Img Shields](https://shields.io)




<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/DauntlessStudio/BedrockUtilities.svg?style=for-the-badge
[contributors-url]: https://github.com/DauntlessStudio/BedrockUtilities/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/DauntlessStudio/BedrockUtilities.svg?style=for-the-badge
[forks-url]: https://github.com/DauntlessStudio/BedrockUtilities/network/members
[stars-shield]: https://img.shields.io/github/stars/DauntlessStudio/BedrockUtilities.svg?style=for-the-badge
[stars-url]: https://github.com/DauntlessStudio/BedrockUtilities/stargazers
[issues-shield]: https://img.shields.io/github/issues/DauntlessStudio/BedrockUtilities.svg?style=for-the-badge
[issues-url]: https://github.com/DauntlessStudio/BedrockUtilities/issues
[license-shield]: https://img.shields.io/github/license/DauntlessStudio/BedrockUtilities.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/DauntlessStudio/BedrockUtilities/master/LICENSE.txt
