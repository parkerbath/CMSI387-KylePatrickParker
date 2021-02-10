# Preliminary Design

## 1.1 – Description of modification/addition to Linux

We will be adding two new features to linux where you can both:

- check the versions of all of the different programming languages currently installed on your system in one command `getAllVersions` (not finalized on the name)
- update all of the versions of the different programming languages currently installed on your system `updateAllVersions` (not finalized on the name)
- potentially a side feature we might implement is when the user checks the versions, the system will output the versions of all of the programming languages
  while also letting the user know how many programming languages need to be updated

## 1.2 – Rationale as to why this is a good idea, or what the good points of it are:

It is common among programmers to check which version of programming language(s) they have installed before working on their project. For example, normally to check which version of node you are using, you may have to use the command `node --version` however with the command `--version` you have to specify which languge individually or use the `&&` operator to produce individual versions such as `python3 --version`. Our new command(s) will provide versions of all languages installed with a single command as well as allowing the user to update all versions to current versions.

## 1.3 – Preliminary list of [possible] Linux modules that will be modified/affected

- `--version`: Although we will not be modifying `--version` we will be `--version` to our `getAllVersions` command.
- `echo`: Referencing `echo` to print the version.
- `apt-get update` Using as a refrence used to pull updates from repositories
- `apt-get upgrade` Using as a reference to upgrade all packages

## 1.4 – Preliminary list of any new modules that you will produce [or 'Not Applicable' if there are none]

We will be using the ability of commands such as `java -version` behind the scenes for each of the installed programming languages to access the information of what version each programming language is. The same goes for updating each of the programming languages.
