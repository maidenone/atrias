# Git #

## TortoiseGit ##

TortoiseGit will not automatically save your login credentials for Google Code. In order to do this, take the following steps:
  1. Create a file named "`_`netrc" in C:\Users\YourUsername with the following content:
```
machine code.google.com
login username@gmail.com
password your-googlecode-password
```
  1. Open up Control Panel > System > Advanced system settings > Advanced (tab) > Environment variables > New... and create a variable named "HOME" and set it to "C:\Users\YourUsername".

TortoiseGit should now remember your login credentials.

## Linux Command Line ##
### Basic Commands ###
See the status of the repository
```
git status
```

Stage changes to commit
```
git add <filename(s) or directory(ies)>
```
Remove files
```
git rm <filename(s) or directory(ies)>
```

Commit changes to the local repository
```
git commit
```

Push changes to the remote repository
```
git push
```

Fetch the remote repository and merge all local branches with their remote equivalents
```
git pull
```

See what's happened
```
git log
```

That's enough to be able to start working. To continue down the rabbit hole, keep reading.

### Working with branches ###
Create a branch off of the current branch
```
git branch <branch name>
```

List local branches
```
git branch
```

List remote branches
```
git branch -r
```

Change branches
```
git checkout <branch name>
```

Merge the changes from <branch name> into the current branch
```
git merge <branch name>
```


### Working with remote repositories ###
Update the local version of the remote repository.  The repository name can be left off if there is only one possibility.
```
git fetch <remote repository>
```

What is in <remote branch> that isn't in <local branch>?
```
git log <remote repo>/<remote branch> ^<local branch>
```

Merge <remote branch> with `<branch>`
```
git checkout <branch>
git merge <remote repo>/<remote branch>
```

Reset `<branch>` to match <remote branch>.  WARNING: The second command will nuke all local changes
```
git checkout <branch>
git reset --hard <remote repo>/<remote branch>
```