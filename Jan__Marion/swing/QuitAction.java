import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

/**
     * Action pour quitter l'application.
     */
    public class QuitAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        /**
         * Constructeur de l'action.
         * 
         * @param name Nom de l'action.
         */
        public QuitAction(String name) {
            super(name);
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }
