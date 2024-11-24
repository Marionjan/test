import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JTextArea;

/**
 * @file AddLineAction.java
 * @brief Action permettant d'ajouter une ligne de texte à une zone de texte.
 * 
 * Cette classe étend {@link javax.swing.AbstractAction} pour ajouter une ligne spécifique à une {@link javax.swing.JTextArea} chaque fois que l'action est déclenchée.
 * 
 */

 /**
  * @class AddLineAction
  * @brief Action permettant d'ajouter une ligne de texte à une zone de texte.
  */
public class AddLineAction extends AbstractAction {
    private static final long serialVersionUID = 1L;

    /** Zone de texte à modifier */
    private JTextArea textArea;

    /** Ligne de texte à ajouter à la zone de texte */
    private final String lineToAdd;

    /**
     * Constructeur de l'action.
     * 
     * @param name      Nom de l'action. Ce nom peut être utilisé pour identifier l'action dans l'interface utilisateur.
     * @param textArea  La zone de texte où la ligne sera ajoutée.
     * @param lineToAdd La ligne de texte à ajouter à la zone de texte lorsque l'action est déclenchée.
     */
    public AddLineAction(String name, JTextArea textArea, String lineToAdd) {
        super(name);
        this.textArea = textArea;
        this.lineToAdd = lineToAdd;
    }

    /**
     * Méthode appelée lorsque l'action est déclenchée.
     * 
     * Cette méthode ajoute la ligne spécifiée à la fin du texte existant dans la {@link JTextArea}.
     * 
     * @param e L'événement de l'action qui a été déclenchée (non utilisé ici).
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        textArea.append(lineToAdd);
    }
}
