public class PromptVault {
    // Points to the first and last prompt in the doubly linked list
    Prompt head;
    Prompt tail;

    // Displays all prompts from head to tail
    public void printPrompts(){
        // Start traversal from the beginning of the list
        Prompt temp = head;
        // Check if the PromptVault is empty.
        if(head == null){
            System.out.println("PromptVault is empty.");
            return;
        }
        // Traverse the list and display each prompt
        while(temp != null){
            System.out.println(temp.promptID+" "+temp.category+" "+temp.promptName+" "+temp.priority);
            temp = temp.next;
        }
    }

    // Deletes a prompt using its Prompt ID
    public void deletePrompt(String promptId){
        // Check if the list is already empty
        if(head == null){
            System.out.println("PromptVault is empty.");
            return;
        }
        // Traverse the list to search for the prompt
        Prompt temp = head;
        while(temp != null){
            // Entered because the Prompt is found
            if (temp.promptID.equals(promptId)){
                // Deletes the first node
                if(temp == head){
                    head = head.next;
                    if(head != null){
                        head.prev = null;
                    }else{
                        tail = null;
                    }
                // Deletes the last node
                }else if(temp == tail){
                    if(tail != null){
                        tail = tail.prev;
                        tail.next = null;
                    }
                // Delete a middle node
                }else{
                    temp.prev.next = temp.next;
                    temp.next.prev = temp.prev;
                }
                System.out.println("Prompt "+promptId+" deleted.");
                return;
            }
            // Move to the temp to next node
            temp = temp.next;
        }
        // Displays the Prompt ID not found
        System.out.println("Prompt "+promptId+" not found.");
    }  
    // Displays prompts in the reverse order
    public void reversePrint(){
        // Check if the list is empty
        if(tail == null){
            System.out.println("PromptVault is empty.");
            return;
        }
        // Starting the traversal from the last node
        Prompt temp = tail;
        //Starts to traverse backwards using previous link if temp not equal to null.
        while(temp != null){
            System.out.println(temp.promptID+" "+temp.category+" "+temp.promptName+" "+temp.priority);
            temp = temp.prev;
        }
    }

    // This method sorts prompts based on priority (High -> Medium -> Low)
    public void sortbyPriority(){

        // Separate lists for each priority
        Prompt highHead = null, highTail = null;
        Prompt mediumHead = null, mediumTail = null;
        Prompt lowHead = null, lowTail = null;

        // Traverse the original list
        Prompt temp = head;
        Prompt nextNode = null;

        while(temp != null){
            // Store next node before disconnecting
            nextNode = temp.next;
            // Disconnect current node
            temp.next = null;
            temp.prev = null;

            // Add the node tohigh priority list
            if (temp.priority.equals("High")){
                if (highHead == null) {
                    highHead = temp;
                    highTail = temp;
                } else {
                    highTail.next = temp;
                    temp.prev = highTail;
                    highTail = temp;
                }
            // Add node to medium priority list
            }else if(temp.priority.equals("Medium")){

                if (mediumHead == null) {
                    mediumHead = temp;
                    mediumTail = temp;
                } else {
                    mediumTail.next = temp;
                    temp.prev = mediumTail;
                    mediumTail = temp;
                }
            // Add node to low priority list
            }else{
                if(lowHead == null){
                    lowHead = temp;
                    lowTail = temp;
                }else{
                    lowTail.next = temp;
                    temp.prev = lowTail;
                    lowTail = temp;
                }
            }
            // Continue with the next node
            temp = nextNode;
        }

        // Connect the high list with the medium or low list
        if(highTail != null){
            if(mediumHead != null){
                highTail.next = mediumHead;
                mediumHead.prev = highTail;
            }else if(lowHead != null){
                highTail.next = lowHead;
                lowHead.prev = highTail;
            }
        }
        // Connect medium list with low list
        if(mediumTail != null && lowHead != null){
            mediumTail.next = lowHead;
            lowHead.prev = mediumTail;
        }
        // Update the head of the sorted list
        if(highHead != null){
            head = highHead;
        }else if(mediumHead != null){
            head = mediumHead;
        }else{
            head = lowHead;
        }
        // update the tail of the sorted list
        if(lowTail != null){
            tail = lowTail;
        }else if(mediumTail != null){
            tail = mediumTail;
        }else{
            tail = highTail;
        }
        // Displaying the sorted PromptVault
        printPrompts();
    }

    // This method adds a new prompt to the end of the list
    public void addPrompt(String promptID , String promptName , String category , String priority){
        Prompt newNode = new Prompt();

        newNode.promptID = promptID;
        newNode.promptName = promptName;
        newNode.category = category;
        newNode.priority = priority;

        // If there are no nodes, insert the first node
        if(head == null){
            head = newNode;
            tail = newNode;
        // If nodes already exist, insert at the end of the list
        }else{
            tail.next = newNode;
            newNode.prev = tail;
            tail = newNode;
        }

        System.out.println("Prompt " + promptID + " added.");
    }

}