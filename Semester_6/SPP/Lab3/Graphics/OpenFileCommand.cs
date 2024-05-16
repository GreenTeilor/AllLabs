using System;
using System.Windows.Input;

namespace AssemblyBrowser
{
    public class OpenFileCommand : ICommand
    {
        // Change command source
        public event EventHandler CanExecuteChanged
        {
            add => CommandManager.RequerySuggested += value;
            remove => CommandManager.RequerySuggested -= value;
        }

        // Single operation on form - open file
        public OpenFileCommand(Action execute, Func<object, bool> canExecute = null)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        private Action _execute;
        private Func<object, bool> _canExecute;

        // Check, if command can be executed
        public bool CanExecute(object parameter)
        {
            return _canExecute == null || CanExecute(parameter);
        }
 
        public void Execute(object parameter)
        {
            _execute();
        }
    }
}
