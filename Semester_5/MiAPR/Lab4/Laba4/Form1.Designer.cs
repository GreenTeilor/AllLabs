namespace Laba4
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.listBox = new System.Windows.Forms.ListBox();
            this.listBoxFunctions = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox_Classes = new System.Windows.Forms.TextBox();
            this.textBox_Objects = new System.Windows.Forms.TextBox();
            this.textBox_Attributes = new System.Windows.Forms.TextBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button1.Location = new System.Drawing.Point(16, 258);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(190, 65);
            this.button1.TabIndex = 0;
            this.button1.Text = "Создать \r\nобучающую выборку";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(310, 346);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(150, 22);
            this.label1.TabIndex = 6;
            this.label1.Text = "Тестовый образ:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(12, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(179, 22);
            this.label2.TabIndex = 7;
            this.label2.Text = "Количество классов";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Location = new System.Drawing.Point(12, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(250, 22);
            this.label3.TabIndex = 8;
            this.label3.Text = "Количество образов в классе";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Location = new System.Drawing.Point(12, 173);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(296, 22);
            this.label4.TabIndex = 9;
            this.label4.Text = "Размер вектора признаков образа";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // listBox
            // 
            this.listBox.Font = new System.Drawing.Font("Times New Roman", 15.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listBox.FormattingEnabled = true;
            this.listBox.ItemHeight = 24;
            this.listBox.Location = new System.Drawing.Point(314, 12);
            this.listBox.Name = "listBox";
            this.listBox.ScrollAlwaysVisible = true;
            this.listBox.Size = new System.Drawing.Size(522, 172);
            this.listBox.TabIndex = 10;
            // 
            // listBoxFunctions
            // 
            this.listBoxFunctions.Font = new System.Drawing.Font("Times New Roman", 15.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listBoxFunctions.FormattingEnabled = true;
            this.listBoxFunctions.ItemHeight = 24;
            this.listBoxFunctions.Location = new System.Drawing.Point(314, 199);
            this.listBoxFunctions.Name = "listBoxFunctions";
            this.listBoxFunctions.ScrollAlwaysVisible = true;
            this.listBoxFunctions.Size = new System.Drawing.Size(522, 124);
            this.listBoxFunctions.TabIndex = 11;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(550, 384);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(185, 43);
            this.button2.TabIndex = 12;
            this.button2.Text = "Определить класс";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox_Classes
            // 
            this.textBox_Classes.Location = new System.Drawing.Point(16, 34);
            this.textBox_Classes.Name = "textBox_Classes";
            this.textBox_Classes.Size = new System.Drawing.Size(92, 29);
            this.textBox_Classes.TabIndex = 13;
            this.textBox_Classes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_Classes_KeyPress);
            // 
            // textBox_Objects
            // 
            this.textBox_Objects.Location = new System.Drawing.Point(16, 117);
            this.textBox_Objects.Name = "textBox_Objects";
            this.textBox_Objects.Size = new System.Drawing.Size(92, 29);
            this.textBox_Objects.TabIndex = 14;
            this.textBox_Objects.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_Classes_KeyPress);
            // 
            // textBox_Attributes
            // 
            this.textBox_Attributes.Location = new System.Drawing.Point(16, 198);
            this.textBox_Attributes.Name = "textBox_Attributes";
            this.textBox_Attributes.Size = new System.Drawing.Size(92, 29);
            this.textBox_Attributes.TabIndex = 15;
            this.textBox_Attributes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_Classes_KeyPress);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.BackgroundColor = System.Drawing.SystemColors.Window;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.ColumnHeadersVisible = false;
            this.dataGridView1.Location = new System.Drawing.Point(314, 384);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.Size = new System.Drawing.Size(206, 43);
            this.dataGridView1.TabIndex = 16;
            this.dataGridView1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_Classes_KeyPress);
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(869, 461);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.textBox_Attributes);
            this.Controls.Add(this.textBox_Objects);
            this.Controls.Add(this.textBox_Classes);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.listBoxFunctions);
            this.Controls.Add(this.listBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Font = new System.Drawing.Font("Times New Roman", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Метод Персептрона";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.ListBox listBoxFunctions;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBox_Classes;
        private System.Windows.Forms.TextBox textBox_Objects;
        private System.Windows.Forms.TextBox textBox_Attributes;
        private System.Windows.Forms.DataGridView dataGridView1;
    }
}

