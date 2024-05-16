using AssemblyBrowserLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Windows.Input;

namespace AssemblyBrowser
{
    public class ViewModel : INotifyPropertyChanged
    {
        // Object to parse structure
        private readonly IAssemblyBrowser _model = new AssemblyBrowserLib.AssemblyBrowser();
        // File path
        private string _openedFile;

        public ViewModel()
        {
            // List of all namespaces
            Containers = new List<ContainerInfo>();
        }

        public List<ContainerInfo> Containers { get; set; }

        // For each property, that requires notification about changes, OnPropertyChanged is called
        // on each property update
        public string OpenedFile
        {
            get
            {
                return _openedFile;
            }
            set
            {
                _openedFile = value;
                Containers = null;
                try
                {
                    // Get all namespaces found in assembly
                    Containers = new List<ContainerInfo>(_model.GetNamespaces(value)); 
                }
                catch (Exception e)
                {
                    _openedFile = $"Error: [{e.Message}]";
                }
                OnPropertyChanged(nameof(Containers));
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        // Method to catch change(choose filePath)
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public ICommand OpenFile { get { return new OpenFileCommand(OpenAssembly); } }

        public void OpenAssembly()
        {
            // Open file open dialog dialog
            using (var openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = @"Assemblies|*.dll;*.exe";
                openFileDialog.Title = @"Select assembly";
                openFileDialog.Multiselect = false;
                // If file was selected
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    // Set filename
                    OpenedFile = openFileDialog.FileName;

                    //Call to display assembly tree
                    OnPropertyChanged(nameof(OpenedFile));
                }
            }
        }
    }
}
