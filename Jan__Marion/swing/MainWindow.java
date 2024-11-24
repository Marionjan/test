/**
 * @file MainWindow.java
 * @brief Main user interface for the Multimedia Client application.
 * 
 * This class represents the main window of the Multimedia Client, allowing the user to interact with the client by
 * searching for, playing, and creating multimedia objects. The interface provides a text area for displaying server
 * responses, input fields for specifying the object name, and buttons for sending commands to the server.
 * 
 * The window also includes a status bar to display the current status of the application.
 * 
 * @author Marion Jan
 * @version 1.0
 * @date 2024
 */

 import javax.swing.*;
 import java.awt.*;
 import java.awt.event.ActionEvent;
 
 /**
  * Main window class for the Multimedia Client application.
  * 
  * This class provides the user interface for interacting with the multimedia client, including:
  * - A text area for displaying server responses.
  * - A text field for entering object names.
  * - Buttons for searching, playing, and creating multimedia objects.
  * - A status label that shows the current state of the client.
  * 
  * The client communicates with the server to send commands and receive responses.
  */

  /**
  * @class MainWindow
  * @brief Represents the main window of the Multimedia Client application.
  */
 public class MainWindow extends JFrame {
     private static final long serialVersionUID = 1L;
 
     private JTextArea textArea;
     private JTextField nameField;
     private JButton searchButton, playButton, createButton;
     private JLabel statusLabel;
     private Client client;
 
     /**
      * Constructor for the MainWindow class.
      * 
      * Initializes the main window with UI components, sets up the connection to the server, and configures event handlers
      * for user interactions (search, play, and create actions).
      */
     public MainWindow() {
         setTitle("Client Multimédia");
         setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         setLayout(new BorderLayout(10, 10));
 
         // Set color palette
         Color backgroundColor = new Color(240, 240, 250);
         Color panelColor = new Color(220, 220, 240);
         getContentPane().setBackground(backgroundColor);
 
         // Use system look and feel
         try {
             UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
         } catch (Exception ignored) { }
 
         // Response display area
         textArea = new JTextArea(10, 40);
         textArea.setEditable(false);
         textArea.setFont(new Font("Arial", Font.PLAIN, 14));
         JScrollPane scrollPane = new JScrollPane(textArea);
         scrollPane.setBorder(BorderFactory.createTitledBorder("Réponses du Serveur"));
         add(scrollPane, BorderLayout.CENTER);
 
         // Name input field
         JPanel inputPanel = new JPanel(new BorderLayout(10, 10));
         inputPanel.setBackground(panelColor);
         nameField = new JTextField();
         nameField.setToolTipText("Entrez le nom ici.");
         inputPanel.add(new JLabel("Nom : "), BorderLayout.WEST);
         inputPanel.add(nameField, BorderLayout.CENTER);
 
         // Action buttons
         JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 10, 10));
         buttonPanel.setBackground(panelColor);
         searchButton = new JButton("Rechercher");
         playButton = new JButton("Jouer");
         createButton = new JButton("Créer");
 
         searchButton.setToolTipText("Rechercher un objet multimédia.");
         playButton.setToolTipText("Jouer un objet multimédia.");
         createButton.setToolTipText("Créer un nouvel objet multimédia.");
 
         buttonPanel.add(searchButton);
         buttonPanel.add(playButton);
         buttonPanel.add(createButton);
 
         inputPanel.add(buttonPanel, BorderLayout.SOUTH);
         add(inputPanel, BorderLayout.SOUTH);
 
         // Status bar
         statusLabel = new JLabel("Prêt.");
         statusLabel.setOpaque(true);
         statusLabel.setBackground(new Color(200, 200, 220));
         statusLabel.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 10));
         add(statusLabel, BorderLayout.NORTH);
 
         // Event handling for buttons
         searchButton.addActionListener(this::handleSearch);
         playButton.addActionListener(this::handlePlay);
         createButton.addActionListener(this::handleCreate);
 
         // Server connection
         try {
             client = new Client("localhost", 3331);
             appendToTextArea("Connecté au serveur localhost:3331");
         } catch (Exception e) {
             appendToTextArea("Erreur : Impossible de se connecter au serveur.");
             setButtonsEnabled(false);
         }
 
         pack();
         setVisible(true);
     }
 
     /**
      * Handles the "Rechercher" button click event.
      * 
      * Sends a search command to the server for the object specified in the name field.
      * 
      * @param event The action event triggered by the "Rechercher" button.
      */
     private void handleSearch(ActionEvent event) {
         sendCommandToServer("search object " + nameField.getText().trim());
     }
 
     /**
      * Handles the "Jouer" button click event.
      * 
      * Sends a play command to the server for the object specified in the name field.
      * 
      * @param event The action event triggered by the "Jouer" button.
      */
     private void handlePlay(ActionEvent event) {
         sendCommandToServer("play " + nameField.getText().trim());
     }
 
     /**
      * Handles the "Créer" button click event.
      * 
      * Opens a new dialog to create a new multimedia object.
      * 
      * @param event The action event triggered by the "Créer" button.
      */
     private void handleCreate(ActionEvent event) {
         new CreateDialog(this, client).setVisible(true);
     }
 
     /**
      * Sends a command to the server and updates the UI with the server's response.
      * 
      * @param command The command to send to the server.
      */
     private void sendCommandToServer(String command) {
         if (client == null) {
             appendToTextArea("Erreur : Client non initialisé.");
             return;
         }
 
         try {
             statusLabel.setText("Envoi de la commande...");
             String response = client.send(command);
             appendToTextArea("Commande : " + command);
             appendToTextArea("Réponse : " + response);
             statusLabel.setText("Prêt.");
         } catch (Exception e) {
             appendToTextArea("Erreur lors de l'envoi de la commande : " + e.getMessage());
             statusLabel.setText("Erreur.");
         }
     }
 
     /**
      * Appends the specified text to the response text area.
      * 
      * @param text The text to append to the text area.
      */
     private void appendToTextArea(String text) {
         textArea.append(text + "\n");
     }
 
     /**
      * Enables or disables the action buttons (search, play, create).
      * 
      * @param enabled Whether the buttons should be enabled.
      */
     private void setButtonsEnabled(boolean enabled) {
         searchButton.setEnabled(enabled);
         playButton.setEnabled(enabled);
         createButton.setEnabled(enabled);
     }
 
     /**
      * Main method to launch the Multimedia Client application.
      * 
      * @param args Command-line arguments (not used).
      */
     public static void main(String[] args) {
         SwingUtilities.invokeLater(MainWindow::new);
     }
 }
 