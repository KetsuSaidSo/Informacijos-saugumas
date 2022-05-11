namespace WinFormsApp2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtplain = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtencrypt = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtdecrypt = new System.Windows.Forms.RichTextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtplain
            // 
            this.txtplain.Location = new System.Drawing.Point(12, 30);
            this.txtplain.Name = "txtplain";
            this.txtplain.Size = new System.Drawing.Size(396, 96);
            this.txtplain.TabIndex = 0;
            this.txtplain.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "Įvedamas tekstas";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 136);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(104, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Užšifruotas tekstas";
            // 
            // txtencrypt
            // 
            this.txtencrypt.Location = new System.Drawing.Point(12, 154);
            this.txtencrypt.Name = "txtencrypt";
            this.txtencrypt.Size = new System.Drawing.Size(396, 96);
            this.txtencrypt.TabIndex = 2;
            this.txtencrypt.Text = "";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 261);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(109, 15);
            this.label3.TabIndex = 5;
            this.label3.Text = "Dešiftruotas tekstas";
            // 
            // txtdecrypt
            // 
            this.txtdecrypt.Location = new System.Drawing.Point(12, 279);
            this.txtdecrypt.Name = "txtdecrypt";
            this.txtdecrypt.Size = new System.Drawing.Size(396, 96);
            this.txtdecrypt.TabIndex = 4;
            this.txtdecrypt.Text = "";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(428, 30);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(94, 45);
            this.button1.TabIndex = 6;
            this.button1.Text = "Užšifruoti";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(428, 81);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(94, 45);
            this.button2.TabIndex = 7;
            this.button2.Text = "Dešifruoti";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(533, 383);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtdecrypt);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtencrypt);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtplain);
            this.Name = "Form1";
            this.Text = "RSA";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private RichTextBox txtplain;
        private Label label1;
        private Label label2;
        private RichTextBox txtencrypt;
        private Label label3;
        private RichTextBox txtdecrypt;
        private Button button1;
        private Button button2;
    }
}