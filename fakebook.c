#include "fakebook.h"

Network *createNetwork()
{
    // Allocate Network
    Network *net = (Network *)malloc(sizeof(Network));
    if (net == NULL)
    {
        return NULL;
    }

    // Allocate users
    net->users = (User **)malloc(sizeof(User *) * NETWORK_CAPACITY);
    if (net->users == NULL)
    {
        free(net);
        return NULL;
    }

    net->numUsers = 0;
    net->capacity = NETWORK_CAPACITY;

    return net;
}

User *createUser(Network *net, const char *name)
{
    if (net == NULL || name == NULL)
    {
        fprintf(stderr, "Invalid Network or Name\n\n");
        return NULL;
    }

    // Check if the network capacity is reached
    if (net->numUsers >= net->capacity)
    {
        fprintf(stderr, "Error: Network is full\n\n");
        return NULL;
    }

    // Allocate user
    User *user = (User *)malloc(sizeof(User));
    if (user == NULL)
    {
        return NULL;
    }

    // Allocate user's friend
    user->friends = (User **)malloc(sizeof(User *) * FRIEND_CAPACITY);
    if (user->friends == NULL)
    {
        free(user);
        return NULL;
    }

    user->id = net->numUsers + 1;
    strncpy(user->name, name, sizeof(user->name));
    user->name[sizeof(user->name) - 1] = '\0';
    user->friendCapacity = FRIEND_CAPACITY;
    user->posts = NULL;

    net->users[net->numUsers] = user;
    net->numUsers += 1;

    printf("User '%s' created with ID %d!\n\n", user->name, user->id);

    return user;
}

void addFriend(User *u1, User *u2)
{
    // Check if user not null
    if (u1 == NULL || u2 == NULL)
    {
        fprintf(stderr, "Error: One or both user IDs are invalid.\n\n");
        return;
    }

    // Check for Self-friendship
    if (u1 == u2)
    {
        fprintf(stderr, "Error: Self-friendship is not allowed.\n\n");
        return;
    }

    // Check if u1 and u2 are already friends
    if (u1->numFriends > 0)
    {
        for (int i = 0; i < u1->numFriends; i++)
        {
            if (u1->friends[i]->id == u2->id)
            {
                printf("%s and %s are already friends!\n\n", u1->name, u2->name);
                return;
            }
        }
    }

    // Add u2 as friend of u1
    u1->friends[u1->numFriends] = u2;
    u1->numFriends += 1;

    // Add u1 as friend of u2
    u2->friends[u2->numFriends] = u1;
    u2->numFriends += 1;

    printf("%s and %s are now friends!\n\n", u1->name, u2->name);
}

void addPost(User *user, const char *content)
{
    if (user == NULL || content == NULL)
    {
        printf("Error: Invalid user or content.\n\n");
        return;
    }

    Post *newPost = (Post *)malloc(sizeof(Post));
    if (newPost == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for new post\n\n");
        return;
    }

    newPost->content = (char *)malloc(sizeof(content) + 1);
    if (content == NULL)
    {
        free(newPost);
        fprintf(stderr, "Failed to allocate memory for content.\n\n");
        return;
    }

    if (user->posts)
    {
        newPost->id = user->posts->id + 1;
    }
    else
    {
        newPost->id = 1;
    }

    strncpy(newPost->content, content, sizeof(content) + 1);
    newPost->next = user->posts;
    user->posts = newPost;

    printf("Post created with ID %d!\n\n", newPost->id);
}

void showFeed(User *user)
{
    if (user == NULL)
    {
        fprintf(stderr, "Error:The provided user ID is invalid.\n\n");
        return;
    }

    int isPostEmpty = 1;

    // User posts
    if (user->posts != NULL)
    {
        isPostEmpty = 0;
        printf("\nYour posts:\n");

        for (Post *post = user->posts; post != NULL; post = post->next)
            printf("   - %s\n", post->content);
    }

    // User direct friends posts
    if (user->numFriends > 0)
    {
        for (int i = 0; i < user->numFriends; i++)
        {
            User *friend = user->friends[i];

            if (friend->posts != NULL)
            {
                isPostEmpty = 0;
                printf("%s posts:\n", friend->name);

                for (Post *post = friend->posts; post != NULL; post = post->next)
                    printf("   - %s\n", post->content);
            }
        }
    }

    // Empty feed
    if (isPostEmpty)
    {
        printf("\nYou don't have any posts yet. Choose option 3 to add posts.");
    }
    printf("\n\n");
}

void showFriends(User *user)
{
    if (user == NULL)
    {
        fprintf(stderr, "Error:The provided user ID is invalid.\n\n");
        return;
    }

    if (user->numFriends > 0)
    {
        printf("%s's friends:\n", user->name);

        for (int i = 0; i < user->numFriends; i++)
        {
            printf("- %s\n", user->friends[i]->name);
        }
    }
    else
    {
        printf("%s doesn't have any friends yet. Choose option 2 to add friends.\n", user->name);
    }

    printf("\n");
}

void displayNetwork(Network *net)
{
    if (net == NULL)
    {
        fprintf(stderr, "Invalid Network\n\n");
        return;
    }

    if (net->numUsers > 0)
    {
        printf("\nAll Users:\n");

        for (int i = 0; i < net->numUsers; i++)
        {

            User *user = net->users[i];
            printf("%d. %s\n", (i + 1), user->name);

            if (user->numFriends > 0)
            {
                printf("     - Friends:\n");

                for (int j = 0; j < user->numFriends; j++)
                {
                    User *friend = user->friends[j];
                    printf("        %d. %s\n", (j + 1), friend->name);
                }
            }
        }

        printf("\n\n");
    }
}

void suggestFriends(User *user)
{
    if (user == NULL)
    {
        fprintf(stderr, "Error:The provided user ID is invalid.\n\n");
        return;
    }

    int *visited = (int *)malloc(sizeof(int) * NETWORK_CAPACITY);
    User **suggested = malloc(sizeof(User *) * NETWORK_CAPACITY);
    if (visited == NULL || suggested == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for suggest Friends.\n");
        free(visited);
        free(suggested);
        return;
    }

    // Initialize all elements of visited and suggested to 0
    for (int i = 0; i < NETWORK_CAPACITY; i++)
    {
        visited[i] = 0;
        suggested[i] = NULL;
    }

    // Visiting head (user) and then first level (user's friends)
    visited[user->id] = 1;
    for (int i = 0; i < user->numFriends; i++)
    {
        visited[user->friends[i]->id] = 1;
    }

    // Queue for BFS
    User **queue = (User **)malloc(sizeof(User *) * NETWORK_CAPACITY);
    if (queue == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for queue.\n");
        free(visited);
        free(suggested);
        return;
    }

    int queueStar = 0;
    int queueEnd = 0;

    // Store direct friends in queue
    for (int i = 0; i < user->numFriends; i++)
    {
        queue[queueEnd] = user->friends[i];
        queueEnd++;
    }

    // Find friends of friends (Level 1)
    while (queueStar < queueEnd)
    {
        User *currentUser = queue[queueStar];

        for (int i = 0; i < currentUser->numFriends; i++)
        {
            User *currentUserFriend = currentUser->friends[i];

            if (!visited[currentUserFriend->id])
            {
                suggested[currentUserFriend->id] = currentUserFriend;
            }
        }
        queueStar++;
    }

    // Print suggested friends
    printf("Suggested friends for %s:\n", user->name);
    int found = 0;
    for (int i = 0; i < NETWORK_CAPACITY; i++)
    {
        if (suggested[i] != NULL)
        {
            printf("  - %s\n", suggested[i]->name);
            found = 1;
        }
    }

    if (!found)
    {
        printf("  (No suggestions found)");
    }

    printf("\n\n");

    free(queue);
    free(visited);
    free(suggested);
}

void freeNetwork(Network *net)
{
    if (net != NULL)
    {
        for (int i = 0; i < net->numUsers; i++)
        {
            User *user = net->users[i];

            // Free posts
            if (user->posts != NULL)
            {
                for (Post *post = user->posts, *next; post != NULL; post = next)
                {
                    next = post->next;
                    free(post->content);
                    free(post);
                }
            }

            free(user->friends);
            free(user);
        }

        free(net->users);
        free(net);
    }
}