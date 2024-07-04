# Java Utils [License badge]()
Java Utils are build tools and utility librairies/classes to use in any java
project. As in **Pimous Dev.** we only use our own productions, this repository
contains everything needed to work without any build automation, dependency
manager or general purpose librairies bundled with a lot of things we don't care
about.

So, these tools are usually updated when we need it. But, if you have any
suggestion or proposal to upgrade this last, don't hesitate to contact us.

## Roadmap
- [ ] Environment files reading & parsing.
- [ ] Cleaning script (Project & Test).
- [ ] Compilation script (Project & Test).
  - [ ] Include ressources on project side.
- [ ] Execution script (Project & Test).
- [ ] A class to give a way to print pretty version of any object inheriting.

## Documentation
Usually, everything is written in files but there is some explanations.

### Technician installation guide
Copy and paste in the root of your project. _But, let your developers do it,
they certainly know more about._

### Developer preparation guide
Copy and paste in the root of your project.

#### Tools
If you're using [VSCode](https://code.visualstudio.com/), take a look at
`.vscode/tasks.json` and the tasks section of the editor. In other cases, bash
scripts under `bin` are documented so you can check them out.

In any cases, if you want to override defaults and so configurate the build
tools for your needs, copy `bin/etc/defaults.env` to your newly created file
`.env`, remove unecessary lines and modify the remaining ones as you want
(Usually `MAIN_CLASS` and `MAIN_CLASS_TEST` properties);

#### Utilities
Read their documentation, import them and use them! Nothing else.

## License
Java Utils (Build tools and Utility librairies/classes)  
Copyright &copy; 2024 - Pimous Dev. (https://www.pimous.dev/)

These programs is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

The latters are distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU General Public License and the GNU
Lesser General Public License along with the programs (Links:
[GNU GPL v3](COPYING) & [GNU LGPL v3](COPYING.LESSER)). If not, see
https://www.gnu.org/licenses/.

## Developers
> Xibitol