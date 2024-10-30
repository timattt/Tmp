# Task 1

![image](https://github.com/user-attachments/assets/0a59b110-3a05-4dd1-8b36-1b924d1dbdba)

# Task 2

<img width="1199" alt="image" src="https://github.com/user-attachments/assets/6c82cb43-6417-4c06-8ad5-501ebba574f3">

# Task 3

![image](https://github.com/user-attachments/assets/6d5c86d9-1afe-46ae-aded-613b68dbf2f1)

# Task 4

## commit-on-wrong-branch

![image](https://github.com/user-attachments/assets/4cd4941a-2ea0-42bd-b9d2-cdb265dba9e5)

```
git checkout master
git branch remote 7958567
git rebase quickfix
git checkout remote
git merge quickfix
```

![image](https://github.com/user-attachments/assets/020e7698-43fd-4d85-9204-c86ab8df1aaa)

## commit-on-wrong-branch 2

![image](https://github.com/user-attachments/assets/3c57543a-cbf3-4179-92ad-48721a73b841)

```
git checkout new-feature
git cherry-pick e4c4dfe
git add .
git commit -m "fix merge conflict"
git checkout master
git reset --hard 414875a
```

![image](https://github.com/user-attachments/assets/2938e755-26b7-4a4c-a140-3becfa9a2272)
