namespace ProtoCSharpForDLL
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
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
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.tbForExpression = new System.Windows.Forms.TextBox();
            this.tbForDerivative = new System.Windows.Forms.TextBox();
            this.Diffbtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tbForExpression
            // 
            this.tbForExpression.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tbForExpression.Location = new System.Drawing.Point(57, 50);
            this.tbForExpression.Name = "tbForExpression";
            this.tbForExpression.Size = new System.Drawing.Size(401, 35);
            this.tbForExpression.TabIndex = 0;
            this.tbForExpression.TextChanged += new System.EventHandler(this.tbForExpression_TextChanged);
            // 
            // tbForDerivative
            // 
            this.tbForDerivative.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tbForDerivative.Location = new System.Drawing.Point(57, 126);
            this.tbForDerivative.Name = "tbForDerivative";
            this.tbForDerivative.ReadOnly = true;
            this.tbForDerivative.Size = new System.Drawing.Size(401, 35);
            this.tbForDerivative.TabIndex = 1;
            // 
            // Diffbtn
            // 
            this.Diffbtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Diffbtn.Location = new System.Drawing.Point(519, 137);
            this.Diffbtn.Name = "Diffbtn";
            this.Diffbtn.Size = new System.Drawing.Size(122, 46);
            this.Diffbtn.TabIndex = 2;
            this.Diffbtn.Text = "Diff";
            this.Diffbtn.UseVisualStyleBackColor = true;
            this.Diffbtn.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(52, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(213, 25);
            this.label1.TabIndex = 3;
            this.label1.Text = "Исходное выражение";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(52, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(353, 25);
            this.label2.TabIndex = 4;
            this.label2.Text = "Дифференциированное выражение";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(653, 198);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Diffbtn);
            this.Controls.Add(this.tbForDerivative);
            this.Controls.Add(this.tbForExpression);
            this.Name = "Form1";
            this.Text = "Алгебраическое дифференциирование";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbForExpression;
        private System.Windows.Forms.TextBox tbForDerivative;
        private System.Windows.Forms.Button Diffbtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

