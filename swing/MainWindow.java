import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

/**
 * Classe principale représentant une fenêtre graphique avec une zone de texte et des boutons.
 * Cette classe dérive de {@link JFrame}.
 * <p>
 * Fonctionnalités :
 * <ul>
 *     <li>Ajout de texte à une zone multi-lignes via deux boutons.</li>
 *     <li>Terminaison de l'application via un troisième bouton.</li>
 *     <li>Initialisation d'un client Java pour communiquer avec un serveur.</li>
 * </ul>
 * </p>
 * 
 * @author Marion Jan
 * @version 2.0
 */

public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;

    private JTextArea textArea;
    private JTextField commandField;
    private JButton searchButton;
    private JButton playButton;
    private JButton createButton;
    private Client client; // Instance du client Java pour communiquer avec le serveur

    public MainWindow() {
        setTitle("Client Multimédia");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Zone de texte pour afficher les réponses du serveur
        textArea = new JTextArea(10, 30);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        // Zone d'entrée pour les commandes
        JPanel inputPanel = new JPanel(new BorderLayout());
        commandField = new JTextField();
        inputPanel.add(commandField, BorderLayout.CENTER);

        // Boutons pour les actions
        searchButton = new JButton("Rechercher");
        playButton = new JButton("Jouer");
        createButton = new JButton("Créer");
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(searchButton);
        buttonPanel.add(playButton);
        buttonPanel.add(createButton);
        inputPanel.add(buttonPanel, BorderLayout.EAST);

        add(inputPanel, BorderLayout.SOUTH);

        // Gestion des événements des boutons
        searchButton.addActionListener(this::handleSearch);
        playButton.addActionListener(this::handlePlay);
        createButton.addActionListener(this::handleCreate);

        // Connexion au serveur
        try {
            client = new Client("localhost", 3331); // Adresse et port du serveur
            appendToTextArea("Connecté au serveur localhost:3331");
        } catch (Exception e) {
            appendToTextArea("Erreur : Impossible de se connecter au serveur.");
            searchButton.setEnabled(false);
            playButton.setEnabled(false);
            createButton.setEnabled(false);
        }

        pack();
        setVisible(true);
    }

    /**
     * Gestion de l'action "Rechercher".
     *
     * @param event L'événement déclenché.
     */
    private void handleSearch(ActionEvent event) {
        String command = "search object " + commandField.getText().trim();
        sendCommandToServer(command);
    }

    /**
     * Gestion de l'action "Jouer".
     *
     * @param event L'événement déclenché.
     */
    private void handlePlay(ActionEvent event) {
        String command = "play " + commandField.getText().trim();
        sendCommandToServer(command);
    }

    /**
     * Gestion de l'action "Créer".
     *
     * @param event L'événement déclenché.
     */
    private void handleCreate(ActionEvent event) {
        new CreateDialog(this, client).setVisible(true);
    }

    /**
     * Envoie une commande au serveur via le client et affiche la réponse.
     *
     * @param command La commande à envoyer.
     */
    private void sendCommandToServer(String command) {
        if (client == null) {
            appendToTextArea("Erreur : Client non initialisé.");
            return;
        }

        try {
            String response = client.send(command);
            appendToTextArea("Commande : " + command);
            appendToTextArea("Réponse : " + response);
        } catch (Exception e) {
            appendToTextArea("Erreur lors de l'envoi de la commande : " + e.getMessage());
        }
    }

    /**
     * Ajoute du texte à la zone de texte.
     *
     * @param text Le texte à ajouter.
     */
    private void appendToTextArea(String text) {
        textArea.append(text + "\n");
    }

    /**
     * Méthode principale pour lancer l'application.
     *
     * @param args Arguments de la ligne de commande (non utilisés).
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(MainWindow::new);
    }
}
