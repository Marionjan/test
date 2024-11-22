import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

/**
 * Interface utilisateur améliorée pour le Client Multimédia.
 */
public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;

    private JTextArea textArea;
    private JTextField commandField;
    private JButton searchButton, playButton, createButton;
    private JLabel statusLabel;
    private Client client;

    public MainWindow() {
        setTitle("Client Multimédia - Interface Améliorée");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(10, 10));

        // Palette de couleurs
        Color backgroundColor = new Color(240, 240, 250);
        Color panelColor = new Color(220, 220, 240);
        getContentPane().setBackground(backgroundColor);
        
        // Look and Feel moderne
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) {
        }

        // Zone d'affichage des réponses
        textArea = new JTextArea(10, 40);
        textArea.setEditable(false);
        textArea.setFont(new Font("Arial", Font.PLAIN, 14));
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setBorder(BorderFactory.createTitledBorder("Réponses du Serveur"));
        add(scrollPane, BorderLayout.CENTER);

        // Zone de saisie de commande
        JPanel inputPanel = new JPanel(new BorderLayout(10, 10));
        inputPanel.setBackground(panelColor);
        commandField = new JTextField();
        commandField.setToolTipText("Entrez une commande ici.");
        inputPanel.add(new JLabel("Commande : "), BorderLayout.WEST);
        inputPanel.add(commandField, BorderLayout.CENTER);

        // Boutons d'action
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

        // Barre d'état
        statusLabel = new JLabel("Prêt.");
        statusLabel.setOpaque(true);
        statusLabel.setBackground(new Color(200, 200, 220));
        statusLabel.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 10));
        add(statusLabel, BorderLayout.NORTH);

        // Gestion des événements
        searchButton.addActionListener(this::handleSearch);
        playButton.addActionListener(this::handlePlay);
        createButton.addActionListener(this::handleCreate);

        // Connexion au serveur
        try {
            client = new Client("localhost", 3331);
            appendToTextArea("Connecté au serveur localhost:3331");
        } catch (Exception e) {
            appendToTextArea("Erreur : Impossible de se connecter au serveur.");
            setButtonsEnabled(false);
        }

        pack();
        setLocationRelativeTo(null); // Centrer la fenêtre
        setVisible(true);
    }

    private void handleSearch(ActionEvent event) {
        sendCommandToServer("search object " + commandField.getText().trim());
    }

    private void handlePlay(ActionEvent event) {
        sendCommandToServer("play " + commandField.getText().trim());
    }

    private void handleCreate(ActionEvent event) {
        new CreateDialog(this, client).setVisible(true);
    }

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

    private void appendToTextArea(String text) {
        textArea.append(text + "\n");
    }

    private void setButtonsEnabled(boolean enabled) {
        searchButton.setEnabled(enabled);
        playButton.setEnabled(enabled);
        createButton.setEnabled(enabled);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(MainWindow::new);
    }
}

