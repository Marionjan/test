import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JTextArea;

/**
     * Action pour ajouter une ligne de texte à la zone de texte.
     */
    public class AddLineAction extends AbstractAction {
        private static final long serialVersionUID = 1L;
        private JTextArea textArea;
        private final String lineToAdd;

        /**
         * Constructeur de l'action.
         * 
         * @param name      Nom de l'action.
         * @param lineToAdd Ligne de texte à ajouter à la zone de texte.
         * @param textArea  Zone de texte modifiée
         */
        public AddLineAction(String name,JTextArea textArea, String lineToAdd) {
            super(name);
            this.textArea = textArea;
            this.lineToAdd = lineToAdd;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            textArea.append(lineToAdd);
        }
    }