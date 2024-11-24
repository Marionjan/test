/**
 * @file CreateDialog.java
 * @brief Dialog window for creating a multimedia object.
 * 
 * This class represents a dialog window that allows users to input information 
 * for creating a multimedia object (e.g., photo, video, film). The dialog provides 
 * input fields for the object's name, path, and additional fields based on the selected type.
 * 
 * The dialog is interactive, with dynamically shown/hid fields based on the type of object 
 * (photo, video, or film). Upon creation, the data is sent to the server for processing.
 * 
 * @author Marion Jan
 * @version 1.0
 * @date 2024
 */

 import javax.swing.*;
 import java.awt.*;
 import java.awt.event.ActionEvent;
 
 /**
  * Represents a dialog window to create a multimedia object (photo, video, or film).
  * The dialog includes fields for entering the name, path, and type-specific properties (e.g., dimensions, duration, chapters).
  * 
  * This class communicates with the server through a Client object.
  */

  /**
  * @class CreateDialog
  * @brief Represents a dialog window for creating a multimedia object.
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
 
     /**
      * Constructor for CreateDialog.
      * 
      * Initializes the dialog with components for entering information about a multimedia object.
      * Fields are dynamically displayed based on the type of object selected (photo, video, or film).
      * 
      * @param parent The parent frame of the dialog.
      * @param client The Client object used to send commands to the server.
      */
     public CreateDialog(JFrame parent, Client client) {
         super(parent, "Créer un objet multimédia", true);
         this.client = client;
 
         // Use the system look and feel
         try {
             UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
         } catch (Exception ignored) { }
 
         setLayout(new BorderLayout());
 
         // Common fields (name and path)
         JPanel commonFieldsPanel = new JPanel(new GridLayout(2, 2));
         commonFieldsPanel.add(new JLabel("Nom :"));
         nameField = new JTextField();
         commonFieldsPanel.add(nameField);
 
         commonFieldsPanel.add(new JLabel("Chemin :"));
         pathField = new JTextField();
         commonFieldsPanel.add(pathField);
         add(commonFieldsPanel, BorderLayout.NORTH);
 
         // Specific fields (dynamically displayed)
         specificFieldsPanel = new JPanel(new GridLayout(4, 2));
         xField = createSpecificField("Dimensions X :", specificFieldsPanel);
         yField = createSpecificField("Dimensions Y :", specificFieldsPanel);
         durationField = createSpecificField("Durée :", specificFieldsPanel);
         chaptersField = createSpecificField("Chapitres : (durées séparées par des virgules)", specificFieldsPanel);
         add(specificFieldsPanel, BorderLayout.CENTER);
 
         // Type selection
         JPanel typePanel = new JPanel();
         JComboBox<String> typeCombo = new JComboBox<>(new String[]{"Photo", "Vidéo", "Film"});
         typeCombo.addActionListener(e -> updateFields(typeCombo.getSelectedItem().toString()));
         typePanel.add(new JLabel("Type :"));
         typePanel.add(typeCombo);
         add(typePanel, BorderLayout.WEST);
 
         // Buttons
         JPanel buttonPanel = new JPanel();
         JButton createButton = new JButton("Créer");
         JButton cancelButton = new JButton("Annuler");
 
         createButton.addActionListener(this::handleCreate);
         cancelButton.addActionListener(e -> dispose());
         buttonPanel.add(createButton);
         buttonPanel.add(cancelButton);
         add(buttonPanel, BorderLayout.SOUTH);
 
         pack();
         updateFields("Photo"); // default: Display photo-specific fields (x, y)
     }
 
     /**
      * Creates and adds a label and text field to a specific fields panel.
      * 
      * @param label The label text for the field.
      * @param panel The panel to which the field will be added.
      * @return The created text field.
      */
     private JTextField createSpecificField(String label, JPanel panel) {
         JLabel fieldLabel = new JLabel(label);
         JTextField textField = new JTextField();
         panel.add(fieldLabel);
         panel.add(textField);
         return textField;
     }
 
     /**
      * Updates the fields displayed in the dialog based on the selected object type.
      * 
      * @param type The type of object selected (e.g., photo, video, or film).
      */
     private void updateFields(String type) {
         // Hide all specific fields
         for (Component comp : specificFieldsPanel.getComponents()) {
             comp.setVisible(false);
         }
 
         switch (type) {
             case "Photo": // Display x, y fields
                 xField.getParent().getComponent(0).setVisible(true);
                 xField.setVisible(true);
                 yField.getParent().getComponent(2).setVisible(true);
                 yField.setVisible(true);
                 break;
 
             case "Vidéo": // Display duration field
                 durationField.getParent().getComponent(4).setVisible(true);
                 durationField.setVisible(true);
                 break;
 
             case "Film": // Display duration and chapters fields
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
 
     /**
      * Handles the creation of the multimedia object when the "Créer" button is clicked.
      * Sends the command to the server and displays the server's response.
      * 
      * @param event The action event triggered by the "Créer" button.
      */
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
 