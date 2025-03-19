#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Constants
#define MAX_TRIES 6
#define WORD_COUNT 60
#define WORD_LENGTH 20
#define MAX_RIDDLES 100
#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 50
#define REQUIRED_CORRECT_ANSWERS 2
#define TOTAL_QUESTIONS 3

// Structure for riddles
typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char answer[MAX_ANSWER_LENGTH];
} Riddle;

// Function Declarations
void numberGuessing();
void rockPaperScissors();
void ticTacToe();
void hangman();
void load_riddles(Riddle riddles[], int *count);
void shuffle_riddles(Riddle riddles[], int count);
int play_game(Riddle riddles[]);
void start_riddle_game();
void playGame(int choice);

// Main Function
int main() {
    int gameChoice;
    char playAgain;

    srand(time(0)); // Seed for random selection

    do {
        printf("\n=== Welcome to the Multi-Game Program! ===\n");
        printf("Do you want to play a random game (1) or choose a game (2)?\n");
        printf("Enter 1 for random or 2 for choosing: ");
        scanf("%d", &gameChoice);

        if (gameChoice == 1) {
            playGame(rand() % 5 + 1); // Pick a random game (1-5)
        } else if (gameChoice == 2) {
            printf("\nSelect a game:\n");
            printf("1. Number Guessing\n");
            printf("2. Rock-Paper-Scissors\n");
            printf("3. Tic-Tac-Toe\n");
            printf("4. Hangman\n");
            printf("5. Room Escape Game\n");
            printf("Enter your choice (1-5): ");
            scanf("%d", &gameChoice);

            if (gameChoice < 1 || gameChoice > 5) {
                printf("Invalid choice! Please choose a valid game.\n");
                continue;
            }

            playGame(gameChoice);
        } else {
            printf("Invalid input! Please enter 1 or 2.\n");
            continue;
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nThanks for playing! Goodbye!\n");
    return 0;
}

// Function to play the selected game
void playGame(int choice) {
    switch (choice) {
        case 1: numberGuessing(); break;
        case 2: rockPaperScissors(); break;
        case 3: ticTacToe(); break;
        case 4: hangman(); break;
        case 5: start_riddle_game(); break;
        default: printf("Invalid game selection!\n");
    }
}

// Number Guessing Game
void numberGuessing() {
    int number, guess, nguesses = 1;
    srand(time(0));
    number = rand() % 100 + 1;

    printf("\n=== Number Guessing Game ===\n");
    printf("Guess a number between 1 and 100.\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess > number) {
            printf("Too high! Try a lower number.\n");
        } else if (guess < number) {
            printf("Too low! Try a higher number.\n");
        } else {
            printf("Congratulations! You guessed the number in %d attempts.\n", nguesses);
        }
        nguesses++;
    } while (guess != number);
}

// Rock-Paper-Scissors Game
void rockPaperScissors() {
    int userChoice, computerChoice;

    srand(time(0));
    computerChoice = rand() % 3 + 1;  // 1 (Rock), 2 (Paper), 3 (Scissors)

    printf("\n=== Rock-Paper-Scissors Game ===\n");
    printf("Choose an option:\n");
    printf("1. Rock\n2. Paper\n3. Scissors\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &userChoice);

    if (userChoice < 1 || userChoice > 3) {
        printf("Invalid choice! Please enter 1, 2, or 3.\n");
        return;
    }

    char *choices[] = {"Rock", "Paper", "Scissors"};
    printf("You chose: %s\n", choices[userChoice - 1]);
    printf("Computer chose: %s\n", choices[computerChoice - 1]);

    if (userChoice == computerChoice) {
        printf("It's a draw!\n");
    } else if ((userChoice == 1 && computerChoice == 3) ||
               (userChoice == 2 && computerChoice == 1) ||
               (userChoice == 3 && computerChoice == 2)) {
        printf("Congratulations! You win! 🎉\n");
    } else {
        printf("Computer wins! Better luck next time. 🤖\n");
    }
}

// Tic-Tac-Toe Game
void ticTacToe() {
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    int turn, winner = 0;
    char player, last_player;

    printf("\n=== Tic-Tac-Toe Game ===\n");

    for (turn = 0; turn < 9 && winner == 0; turn++) {
        player = (turn % 2 == 0) ? 'X' : 'O';
        last_player = player;

        // Display the board
        printf("\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf(" %c ", board[i][j]);
                if (j < 2) printf("|");
            }
            printf("\n");
            if (i < 2) printf("---+---+---\n");
        }

        // Get player's move
        int choice, row, col;
        do {
            printf("Player %c, enter a position (1-9): ", player);
            scanf("%d", &choice);
            row = (choice - 1) / 3;
            col = (choice - 1) % 3;
        } while (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O');

        board[row][col] = player;

        // Check for a winner
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) winner = 1;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) winner = 1;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) winner = 1;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) winner = 1;

        if (winner) break;
    }

    // Display final board
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }

    if (winner) {
        printf("Player %c wins!\n", last_player);
    } else {
        printf("It's a draw!\n");
    }
}

// Hangman Game
void hangman() {
    char *wordList[WORD_COUNT] = {
        "apple", "banana", "cherry", "grapes", "mango", "orange", "peach", "pear", "plum", "strawberry",
        "tiger", "elephant", "giraffe", "lion", "monkey", "panda", "rabbit", "zebra", "kangaroo", "hippopotamus",
        "computer", "keyboard", "mouse", "monitor", "printer", "scanner", "laptop", "desktop", "software", "hardware",
        "car", "bicycle", "motorcycle", "airplane", "helicopter", "submarine", "train", "bus", "truck", "ship",
        "mountain", "river", "ocean", "valley", "desert", "forest", "island", "volcano", "waterfall", "glacier",
        "football", "basketball", "cricket", "tennis", "hockey", "baseball", "badminton", "rugby", "cycling", "swimming"
    };

    srand(time(NULL));
    char word[WORD_LENGTH];
    strcpy(word, wordList[rand() % WORD_COUNT]);
    int wordLength = strlen(word);

    char guessedLetters[WORD_LENGTH] = "";
    char display[WORD_LENGTH];
    char guess;
    int tries = 0, correctGuesses = 0;

    for (int i = 0; i < wordLength; i++) {
        display[i] = '_';
    }

    printf("\n=== Hangman Game ===\n");
    printf("Try to guess the word. You have %d tries.\n", MAX_TRIES);

    while (tries < MAX_TRIES && correctGuesses < wordLength) {
        printf("\nTries left: %d\n", MAX_TRIES - tries);
        for (int i = 0; i < wordLength; i++) {
            printf("%c ", display[i]);
        }
        printf("\n");

        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (strchr(guessedLetters, guess)) {
            printf("You already guessed '%c'. Try again!\n", guess);
            continue;
        }

        strncat(guessedLetters, &guess, 1);

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                display[i] = guess;
                found = 1;
                correctGuesses++;
            }
        }

        if (!found) {
            printf("Wrong guess!\n");
            tries++;
        } else {
            printf("Good guess!\n");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\nCongratulations! You guessed the word: %s\n", word);
    } else {
        printf("\nGame over! The word was: %s\n", word);
    }
}

// Room Escape Game
void start_riddle_game() {
    FILE *file;
    Riddle riddles[MAX_RIDDLES];
    int riddleCount = 0;
    char userAnswer[MAX_ANSWER_LENGTH];
    int correctAnswers = 0;

    // Open the file
    file = fopen("riddle.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open 'riddle.txt'. Ensure the file exists.\n");
        return;
    }

    // Load riddles into array
    while (fgets(riddles[riddleCount].question, MAX_QUESTION_LENGTH, file) != NULL &&
           fgets(riddles[riddleCount].answer, MAX_ANSWER_LENGTH, file) != NULL) {
        // Remove newlines
        riddles[riddleCount].question[strcspn(riddles[riddleCount].question, "\n")] = 0;
        riddles[riddleCount].answer[strcspn(riddles[riddleCount].answer, "\n")] = 0;
        riddleCount++;
        if (riddleCount >= MAX_RIDDLES) break;
    }
    fclose(file);

    if (riddleCount < TOTAL_QUESTIONS) {
        printf("Not enough riddles available. Add more riddles in 'riddle.txt'.\n");
        return;
    }

    // Shuffle riddles
    srand(time(NULL));
    for (int i = 0; i < riddleCount - 1; i++) {
        int j = rand() % riddleCount;
        Riddle temp = riddles[i];
        riddles[i] = riddles[j];
        riddles[j] = temp;
    }

    printf("\n=== Room Escape Game ===\n");
    printf("Solve at least %d out of %d riddles to escape!\n\n", REQUIRED_CORRECT_ANSWERS, TOTAL_QUESTIONS);

    // Ask shuffled riddles
    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        printf("Riddle: %s\n", riddles[i].question);
        printf("Your answer: ");
        fflush(stdin);

        // Proper input handling
        if (!fgets(userAnswer, MAX_ANSWER_LENGTH, stdin)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        userAnswer[strcspn(userAnswer, "\n")] = 0; // Remove newline

        // Convert both to lowercase for case-insensitive comparison
        for (int j = 0; userAnswer[j]; j++) userAnswer[j] = tolower(userAnswer[j]);
        for (int j = 0; riddles[i].answer[j]; j++) riddles[i].answer[j] = tolower(riddles[i].answer[j]);

        if (strcmp(userAnswer, riddles[i].answer) == 0) {
            printf("Correct!\n\n");
            correctAnswers++;
        } else {
            printf("Wrong! The correct answer is: %s\n\n", riddles[i].answer);
        }
    }

    // Result message
    if (correctAnswers >= REQUIRED_CORRECT_ANSWERS) {
        printf("Congratulations! You escaped the room with %d correct answers!\n", correctAnswers);
    } else {
        printf("Game Over! You failed to escape. You got %d correct answers.\n", correctAnswers);
    }
}
