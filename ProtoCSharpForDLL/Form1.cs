using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProtoCSharpForDLL
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public const string CppFincDLL = @"CppDLL.dll";

        //public const string CppFincDLL = @"C:\Users\georg\OneDrive\Рабочий стол\CppDLL\Debug\CppDLL.dll";
        [DllImport(CppFincDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetValue(StringBuilder str, int strlen);

        private void button1_Click(object sender, EventArgs e)
        {
            tbForDerivative.Clear();
            StringBuilder str = new StringBuilder(50);
            
            str.Append(tbForExpression.Text);
            GetValue(str, 50); //не более 50 символов!!!

            tbForDerivative.Text = str.ToString();
        }

        private void tbForExpression_TextChanged(object sender, EventArgs e)
        {
            tbForDerivative.Clear();
        }
    }
}
