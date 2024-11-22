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
    private JPanel specificFieldsPanel;
    private Client client;

    public CreateDialog(JFrame parent, Client client) {
        super(parent, "Créer un objet multimédia", true);
        this.client = client;


        // Utiliser le look and feel du système
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) {
        }
        setLayout(new BorderLayout());

        // Champs communs
        JPanel commonFieldsPanel = new JPanel(new GridLayout(2, 2));
        commonFieldsPanel.add(new JLabel("Nom :"));
        nameField = new JTextField();
        commonFieldsPanel.add(nameField);

        commonFieldsPanel.add(new JLabel("Chemin :"));
        pathField = new JTextField();
        commonFieldsPanel.add(pathField);
        add(commonFieldsPanel, BorderLayout.NORTH);

        // Champs spécifiques (masqués/affichés dynamiquement)
        specificFieldsPanel = new JPanel(new GridLayout(4, 2));
        xField = createSpecificField("Dimensions X :", specificFieldsPanel);
        yField = createSpecificField("Dimensions Y :", specificFieldsPanel);
        durationField = createSpecificField("Durée :", specificFieldsPanel);
        chaptersField = createSpecificField("Chapitres : (durées séparées par des virgules)", specificFieldsPanel);
        add(specificFieldsPanel, BorderLayout.CENTER);

        // Choix du type
        JPanel typePanel = new JPanel();
        JComboBox<String> typeCombo = new JComboBox<>(new String[]{"Photo", "Vidéo", "Film"});
        typeCombo.addActionListener(e -> updateFields(typeCombo.getSelectedItem().toString()));
        typePanel.add(new JLabel("Type :"));
        typePanel.add(typeCombo);
        add(typePanel, BorderLayout.WEST);

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
        updateFields("Photo"); // default : Afficher les champs spécifiques à une photo (x, y)
    }

    private JTextField createSpecificField(String label, JPanel panel) {
        JLabel fieldLabel = new JLabel(label);
        JTextField textField = new JTextField();
        panel.add(fieldLabel);
        panel.add(textField);
        return textField;
    }

    private void updateFields(String type) {
        // Masquer tous les champs spécifiques
        for (Component comp : specificFieldsPanel.getComponents()) {
	    comp.setVisible(false);
        }

        switch (type) {
	    case "Photo": // Afficher les champs x, y
	        xField.getParent().getComponent(0).setVisible(true); 
	        xField.setVisible(true);
	        yField.getParent().getComponent(2).setVisible(true); 
	        yField.setVisible(true);
	        break;

	    case "Vidéo": // Afficher le champ durée
	        durationField.getParent().getComponent(4).setVisible(true); 
	        durationField.setVisible(true);
	        break;

	    case "Film": // Afficher les champs durée et chapitres
	        durationField.getParent().getComponent(4).setVisible(true); 
	        durationField.setVisible(true);
    	        chaptersField.setVisible(true);
	        chaptersField.getParent().getComponent(6).setVisible(true); 
	        break;

	    default:
	        break;
        }

        pack(); 
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
            if (xField.isVisible() && yField.isVisible()) {
                int x = Integer.parseInt(xField.getText().trim());
                int y = Integer.parseInt(yField.getText().trim());
                command = String.format("create photo %s %s %d %d", name, path, x, y);
            } else if (durationField.isVisible() && !chaptersField.isVisible()) {
                int duration = Integer.parseInt(durationField.getText().trim());
                command = String.format("create video %s %s %d", name, path, duration);
            } else if (chaptersField.isVisible()) {
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

