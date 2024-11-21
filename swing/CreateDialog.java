import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

/**
 * Fenêtre de dialogue pour créer un objet multimédia.
 */
public class CreateDialog extends JDialog {
    private JTextField nameField;
    private JTextField pathField;
    private JTextField xField;
    private JTextField yField;
    private JTextField durationField;
    private JTextField chaptersField;
    private Client client;

    public CreateDialog(JFrame parent, Client client) {
        super(parent, "Créer un objet multimédia", true);
        this.client = client;

        setLayout(new BorderLayout());
        JPanel formPanel = new JPanel(new GridLayout(6, 2));

        // Champs communs
        formPanel.add(new JLabel("Nom :"));
        nameField = new JTextField();
        formPanel.add(nameField);

        formPanel.add(new JLabel("Chemin :"));
        pathField = new JTextField();
        formPanel.add(pathField);

        // Champs spécifiques
        formPanel.add(new JLabel("Dimensions X :"));
        xField = new JTextField();
        xField.setEnabled(false); // Par défaut désactivé
        formPanel.add(xField);

        formPanel.add(new JLabel("Dimensions Y :"));
        yField = new JTextField();
        yField.setEnabled(false);
        formPanel.add(yField);

        formPanel.add(new JLabel("Durée :"));
        durationField = new JTextField();
        durationField.setEnabled(false);
        formPanel.add(durationField);

        formPanel.add(new JLabel("Chapitres : (durées séparées par des virgules)"));
        chaptersField = new JTextField();
        chaptersField.setEnabled(false);
        formPanel.add(chaptersField);

        add(formPanel, BorderLayout.CENTER);

        // Choix du type
        JPanel typePanel = new JPanel();
        JComboBox<String> typeCombo = new JComboBox<>(new String[]{"Photo", "Vidéo", "Film"});
        typePanel.add(new JLabel("Type :"));
        typePanel.add(typeCombo);

        typeCombo.addActionListener(e -> updateFields(typeCombo.getSelectedItem().toString()));

        add(typePanel, BorderLayout.NORTH);

        // Boutons
        JPanel buttonPanel = new JPanel();
        JButton createButton = new JButton("Créer");
        JButton cancelButton = new JButton("Annuler");

        createButton.addActionListener(this::handleCreate);
        cancelButton.addActionListener(e -> dispose());

        buttonPanel.add(createButton);
        buttonPanel.add(cancelButton);
        add(buttonPanel, BorderLayout.SOUTH);

        pack();
    }

    private void updateFields(String type) {
        xField.setEnabled(type.equals("Photo"));
        yField.setEnabled(type.equals("Photo"));
        durationField.setEnabled(type.equals("Vidéo") || type.equals("Film"));
        chaptersField.setEnabled(type.equals("Film"));
    }

    private void handleCreate(ActionEvent event) {
        String name = nameField.getText().trim();
        String path = pathField.getText().trim();
        String command = "";

        if (name.isEmpty() || path.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Nom et chemin sont obligatoires.", "Erreur", JOptionPane.ERROR_MESSAGE);
            return;
        }

        try {
            if (xField.isEnabled() && yField.isEnabled()) {
                int x = Integer.parseInt(xField.getText().trim());
                int y = Integer.parseInt(yField.getText().trim());
                command = String.format("create photo %s %s %d %d", name, path, x, y);
            } else if (durationField.isEnabled() && !chaptersField.isEnabled()) {
                int duration = Integer.parseInt(durationField.getText().trim());
                command = String.format("create video %s %s %d", name, path, duration);
            } else if (chaptersField.isEnabled()) {
                int duration = Integer.parseInt(durationField.getText().trim());
                String[] chapters = chaptersField.getText().trim().split(",");
                command = String.format("create film %s %s %d %d %s", name, path, duration, chapters.length, String.join(" ", chapters));
            }

            String response = client.send(command);
            JOptionPane.showMessageDialog(this, "Réponse du serveur : " + response, "Succès", JOptionPane.INFORMATION_MESSAGE);
            dispose();
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Champs numériques invalides.", "Erreur", JOptionPane.ERROR_MESSAGE);
        }
    }
}
