import java.util.Scanner;

//Reads an integer Number of Operations (n) followed by N operation
//PromptVault. The PromptVault stores Prompt records using a custom doubly linked list (no arrays / built-in collections are used).
//Reset explanation(comments) are written right before line of each method calling.
public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        PromptVault vault = new PromptVault();
        System.out.print("Enter number of operations : ");

        int n = 0;
        boolean validInput = true;

        try {
            n = sc.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input! 'n' must be an integer.");
            validInput = false;
        }
        if (!validInput) {
            sc.close();
            return;
        }

        while (n > 0) {
            // Here user is asked to enter the required command to proceed the respective operation.
            String command = sc.next();

            // A <PromptID> <Category> <PromptName> <Priority> - add a prompt
            if (command.equals("A")) {
                String id = sc.next();
                String name = sc.next();
                String category = sc.next();
                String priority = sc.next();

                vault.addPrompt(id, name, category, priority);

                // D <PromptID> - delete a prompt by ID
            } else if (command.equals("D")) {
                String id = sc.next();
                vault.deletePrompt(id);

                // P - print all prompts (insertion order)
            } else if (command.equals("P")) {
                vault.printPrompts();

                // REV - print all prompts (reverse order)
            } else if (command.equals("REV")) {
                vault.reversePrint();

                // S - sort prompts by priority (High -> Medium -> Low) and print
            } else if (command.equals("S")) {
                vault.sortbyPriority();
                // else statement works if user enter invalid command (Entered other than A, D, P, REV, or S.)
            } else {
                System.out.println("Invalid command entered: " + command + ". Please enter A, D, P, REV, or S.");
            }
            n = n - 1;
        }
        sc.close();
    }
}