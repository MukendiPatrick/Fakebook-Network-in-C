#include "fakebook.h"

int main()
{
    Network *net = createNetwork();
    if (net == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for network\n");
        return 1;
    }

    printf("==== Welcome to Fakebook ====\n");
    printf("1. Add new user\n");
    printf("2. Add friendship\n");
    printf("3. Create post\n");
    printf("4. Show user's friends\n");
    printf("5. Show user's feed\n");
    printf("6. Suggest friends\n");
    printf("7. Display entire network\n");
    printf("8. Exit\n");

    while (1)
    {
        int menuOption;
        printf("Enter your choice: ");
        scanf("%d", &menuOption);
        getchar();

        if (menuOption == 1)
        {
            char name[50];

            printf("Enter your name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = '\0';

            User *user = createUser(net, name);
            if (user == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for user\n");
                return 1;
            }
        }
        else if (menuOption == 2)
        {
            int firstUserId;
            int secondUserId;
            printf("Enter first user ID: ");
            scanf("%d", &firstUserId);
            getchar();
            printf("Enter second user ID: ");
            scanf("%d", &secondUserId);
            getchar();

            User *u1 = net->users[firstUserId - 1];
            User *u2 = net->users[secondUserId - 1];

            addFriend(u1, u2);
        }
        else if (menuOption == 3)
        {
            int userId;
            printf("Enter user ID: ");
            scanf("%d", &userId);
            getchar();
            User *user = net->users[userId - 1];

            char content[100];
            printf("Enter your post content: ");
            fgets(content, 100, stdin);
            content[strcspn(content, "\n")] = '\0';

            addPost(user, content);
        }
        else if (menuOption == 4)
        {
            int userId;
            printf("Enter user ID: ");
            scanf("%d", &userId);
            getchar();

            User *user = net->users[userId - 1];
            showFriends(user);
        }
        else if (menuOption == 5)
        {
            int userId;
            printf("Enter user ID: ");
            scanf("%d", &userId);
            getchar();

            User *user = net->users[userId - 1];
            showFeed(user);
        }
        else if (menuOption == 6)
        {
            int userId;
            printf("Enter user ID: ");
            scanf("%d", &userId);
            getchar();

            User *user = net->users[userId - 1];
            suggestFriends(user);
        }
        else if (menuOption == 7)
        {
            displayNetwork(net);
        }
        else if (menuOption == 8)
        {
            break;
        }
        else
        {
            printf("\nInvalid option. Try again.\n");
        }
    }

    freeNetwork(net);
    return 0;
}