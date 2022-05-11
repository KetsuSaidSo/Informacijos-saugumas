using System.Security.Cryptography;
using System;
using System.Text;

namespace WinFormsApp2
{
    public partial class Form1 : Form
    {
        static public byte[] Encryption(byte[] Data, RSAParameters RSAKey, bool DoOAEPPadding)
        {
            try
            {
                byte[] encryptedData;
                using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
                {
                    RSA.ImportParameters(RSAKey);
                    encryptedData = RSA.Encrypt(Data, DoOAEPPadding);
                }
                return encryptedData;
            }
            catch (CryptographicException e)
            {
                Console.WriteLine(e.Message);
                return null;
            }
        }

        static public byte[] Decryption(byte[] Data, RSAParameters RSAKey, bool DoOAEPPadding)
        {
            try
            {
                byte[] decryptedData;
                using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
                {
                    RSA.ImportParameters(RSAKey);
                    decryptedData = RSA.Decrypt(Data, DoOAEPPadding);
                }
                return decryptedData;
            }
            catch (CryptographicException e)
            {
                Console.WriteLine(e.ToString());
                return null;
            }
        }

        UnicodeEncoding ByteConverter = new UnicodeEncoding();
        RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
        RSA de = new RSA();
        byte[] plaintext;
        byte[] encryptedtext;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
                plaintext = ByteConverter.GetBytes(txtplain.Text);
                encryptedtext = Encryption(plaintext, RSA.ExportParameters(false), false);
                txtencrypt.Text = ByteConverter.GetString(encryptedtext);
        }

        private void button2_Click(object sender, EventArgs e)
        {
                byte[] decryptedtex = Decryption(encryptedtext,
                RSA.ExportParameters(true), false);
                txtdecrypt.Text = ByteConverter.GetString(decryptedtex);
        }
    }
}