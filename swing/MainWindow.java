import javax.swing.*;
import java.awt.*;

/**
 * Classe principale représentant une fenêtre graphique avec une zone de texte et des boutons.
 * Cette classe dérive de {@link JFrame}.
 * <p>
 * Fonctionnalités :
 * <ul>
 *     <li>Ajout de texte à une zone multi-lignes via deux boutons.</li>
 *     <li>Terminaison de l'application via un troisième bouton.</li>
 * </ul>
 * </p>
 * 
 * @author Marion Jan
 * @version 1.0
 */
public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;

    /**
     * Zone de texte principale où les actions sont enregistrées.
     */
    private JTextArea textArea;

    /**
     * Constructeur principal pour initialiser l'interface graphique.
     */
    public MainWindow() {
        // Configuration de la fenêtre principale
        setTitle("Fenêtre principale");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Initialisation de la zone de texte
        textArea = new JTextArea(10, 30);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        // Création et ajout de la barre de menus
        setJMenuBar(createMenuBar());

        // Création et ajout de la barre d'outils
        add(createToolBar(), BorderLayout.SOUTH);

        // Ajustement et affichage de la fenêtre
        pack();
        setVisible(true);
    }

    /**
     * Crée la barre de menus.
     * 
     * @return un objet JMenuBar contenant les menus et leurs actions.
     */
    private JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();

        // Création du menu "Actions"
        JMenu actionMenu = new JMenu("Actions");
        actionMenu.add(new AddLineAction("Ajouter Ligne 1", textArea,  "Ligne ajoutée par bouton 1 (menu)\n"));
        actionMenu.add(new AddLineAction("Ajouter Ligne 2", textArea,  "Ligne ajoutée par bouton 2 (menu)\n"));
        actionMenu.add(new QuitAction("Quitter"));

        menuBar.add(actionMenu, BorderLayout.NORTH);
        return menuBar;
    }

    /**
     * Crée la barre d'outils.
     * 
     * @return un objet JToolBar contenant les boutons et leurs actions.
     */
    private JToolBar createToolBar() {
        JToolBar toolBar = new JToolBar();

        // Ajout des actions dans la barre d'outils
        toolBar.add(new AddLineAction("Ligne 1", textArea, "Ligne ajoutée par bouton 1 (bottom)\n"));
        toolBar.add(new AddLineAction("Ligne 2", textArea, "Ligne ajoutée par bouton 2 (bottom)\n"));
        toolBar.add(new QuitAction("Quitter"));

        return toolBar;
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
