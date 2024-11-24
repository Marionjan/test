/**
 * @file QuitAction.java
 * @brief Action to exit the application.
 * 
 * This class defines an action to quit the application when triggered. It extends {@link AbstractAction} and overrides
 * the {@link actionPerformed} method to call {@link System#exit} with a status code of 0, terminating the program.
 * 
 * @author Marion Jan
 * @version 1.0
 * @date 2024
 */

 import java.awt.event.ActionEvent;
 import javax.swing.AbstractAction;
 
 /**
  * Action to quit the application.
  * 
  * This class implements an action that can be assigned to a button or menu item to close the application.
  * When the action is triggered, the {@link #actionPerformed} method is called, which terminates the program.
  */

  /**
  * @class QuitAction
  * @brief Represents an administrator in the system.
  */
 public class QuitAction extends AbstractAction {
     private static final long serialVersionUID = 1L;
 
     /**
      * Constructor for the QuitAction class.
      * 
      * @param name The name of the action. This will be displayed on buttons or menu items that use this action.
      */
     public QuitAction(String name) {
         super(name);
     }
 
     /**
      * Performs the action to quit the application.
      * 
      * When triggered, this method calls {@link System#exit} with a status code of 0, terminating the program.
      * 
      * @param e The action event triggered when the action is performed.
      */
     @Override
     public void actionPerformed(ActionEvent e) {
         System.exit(0);
     }
 }
 