/*
This shows a single node of PromptVault's doubly linked list.
Each Prompt stores 1 AI prompt's details along with the links to the previous and next Prompt in the list.
*/

class Prompt {
    String promptID;
    String category;
    String promptName;
    String priority;

    Prompt next;
    Prompt prev;
}