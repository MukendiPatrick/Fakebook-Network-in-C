# Fakebook-Network-in-C
A graph-driven social app built in C lets people link up, share posts, and explore friend suggestions; all through terminal interaction. Implemented dynamic arrays, structs, pointers, and reusable functions to manage users, posts, friendships, and network operations. 

## Compilation

#### Compile:

```bash
gcc -Wall -Wextra -Werror main.c fakebook.c -o fakebook.o
```
#### Run

```bash
./fakebook.o
```

## Menu Option

| Menu Option | Action / Description |
|-------------|--------------------|
| 1 | **Add new user**: Prompt for a name and create a new user. |
| 2 | **Add friendship**: Prompt for two user IDs and create a bidirectional friendship. |
| 3 | **Create post**: Prompt for a user ID and post content, then add the post to the user’s feed. |
| 4 | **Show user’s friends**: Prompt for a user ID and display all their friends. |
| 5 | **Show user’s feed**: Prompt for a user ID and display posts by the user and their direct friends. |
| 6 | **Suggest friends**: Prompt for a user ID and suggest friends using friends-of-friends (BONUS, via BFS). |
| 7 | **Display entire network**: Show all users and their friendships. |
| 8 | **Exit**: Terminate the program. |

#### You will see the following menu:

==== Welcome to Fakebook ====
1. Add new user
2. Add friendship
3. Create post
4. Show user’s friends
5. Show user’s feed
6. Suggest friends
7. Display entire network
8. Exit
Enter your choice:


## Functions

| Function | Description |
|----------|-------------|
| `Network *createNetwork();` | Initialize an empty Fakebook network. |
| `User *createUser(Network *net, const char *name);` | Add a new user with the given name. |
| `void addFriend(User *u1, User *u2);` | Create a friendship between two users (bidirectional). |
| `void addPost(User *user, const char *content);` | Add a new post to a user’s feed. |
| `void showFriends(User *user);` | Print all the user’s friends. |
| `void showFeed(User *user);` | Show posts by the user and their direct friends. |
| `void suggestFriends(User *user);` | **BONUS:** Suggest new friends using friends-of-friends (via BFS). |
| `void displayNetwork(Network *net);` | Print all users and their connections. |

## Project Files

| File | Description |
|------|-------------|
| `fakebook.h` | Contains the structs and function prototypes for the Fakebook network. |
| `fakebook.c` | Implements the functions declared in `fakebook.h`. |
| `main.c` | Provides the terminal-based user interface and menu interaction. |
| `README.txt` | Project documentation, instructions, and usage examples. |




