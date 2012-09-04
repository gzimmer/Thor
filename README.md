![Thor](http://adronhall.smugmug.com/Software/Software-Development/Pyrocumulus/i-NqSGc4m/0/S/Marvel-vs-Capcom-3-MVC3-S.jpg "Thor")
Project Thor Overview
===
The Thor Project is setup to deliver a high quality, solid user experience, and resilient user interface for Cloud Foundry (w/ Iron Foundry Extension Support) PaaS enabled systems to the Apple OS-X System. This project, to ensure a solid user experience utilizes the Cocoa Framework.

_**Please fork and contribute back.**_ If you'd like to contact the team working on Thor so we can discuss our current road map, please feel free to contact me [Adron Hall](https://github.com/Adron/) via Twitter [@Adron](https://twitter.com/#!/adron) or e-mail me <adron.hall@tier3.com>. You can also of course message me directly via Github.
License
---
Copyright 2012 Iron Foundry Organization

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

   Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

Technology & Tools Used
---
The tools used to create, build and maintain this project include Xcode. So far there is no other peripheral software used at this time, of course, that is always subject to change.
Technical Description
---
This application uses the [VMC CLI](https://github.com/cloudfoundry/vmc) or  [Iron Foundry VMC CLI for .NET](https://github.com/IronFoundry/vmc) as an underlying tool. The VMC tool acts as an abstraction layer to protect from changes that are made to the underlying cloud controller and other Cloud Foundry architecture.
Workflow
---
**What's Being Worked On?**

The workflow we're using for Thor is viewable via the [Issues](https://github.com/IronFoundry/Thor/issues) section used in conjunction with the [Huboard Kanban](http://huboard.com/IronFoundry/Thor/board).

The Kanban follows a simple backlog (with as minimum of a backlog kept as possible), then that becomes working, and steps through the remaining items as work is completed.

**Getting the Code**

To clone/fork/download the latest code to work with, contribute, and send pull requests with follow these steps.

 1. Navigate to the main source (where you probably already are since you're reading this document) and fork the code. [Thor Source Code](https://github.com/IronFoundry/Thor)
 2. Once you've forked the code, navigate to your repository and clone to your local development machine.

`git clone git@github.com:YourGithubAccount/Thor.git`

 3. Once the clone is complete, pull the submodules with the following command.

`git submodule update --init --recursive`

Your local repository should have executable code now. Open the project with XCode and see if everything works. If it doesn't, please post a comment or message me via my github account [Adron](https://github.com/Adron) or msg me on Twitter [@Adron](http://twitter.com/adron) and I'll help you get everything up and running.

**Working on the Code**

Once you've added the feature, or completed one of the stories or items in the [Issues List](https://github.com/IronFoundry/Thor/issues?state=open) leave a comment on the issue and submit a pull request (or just submit the pull request). I'll then merge it back in, or if there are conflicts I'll work with you to merge it back in and add the code to the master branch.