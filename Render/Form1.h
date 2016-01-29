#pragma once
#define Y_MAX 500
#define X_MAX 500
namespace Render {
    
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    
    Scene::MyScene scene(X_MAX, Y_MAX);
   
    public ref class Form1 : public System::Windows::Forms::Form
    {
   
    public:
        Form1(void)
        {
            InitializeComponent();
            this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
            //Bitmap
            this->MyImage = gcnew Bitmap(scene.Width(), scene.Height() );
            
        }

    protected:
        Bitmap ^MyImage; 

        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::PictureBox^  pictureBox1;
    private: System::Windows::Forms::Button^  Button_AddFigs;


    protected: 

    private: System::Windows::Forms::ListBox^  listBox1;
    private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
    private: System::Windows::Forms::Button^  Button_DelSelFig;


    private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

        void InitializeComponent(void)
        {
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->Button_AddFigs = (gcnew System::Windows::Forms::Button());
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->Button_DelSelFig = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
            this->SuspendLayout();
            // 
            // pictureBox1
            // 
            this->pictureBox1->Location = System::Drawing::Point(160, 89);
            this->pictureBox1->MaximumSize = System::Drawing::Size(2000, 2000);
            this->pictureBox1->MinimumSize = System::Drawing::Size(100, 100);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(300, 300);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            // 
            // Button_AddFigs
            // 
            this->Button_AddFigs->Location = System::Drawing::Point(12, 12);
            this->Button_AddFigs->Name = L"Button_AddFigs";
            this->Button_AddFigs->Size = System::Drawing::Size(78, 31);
            this->Button_AddFigs->TabIndex = 1;
            this->Button_AddFigs->Text = L"AddFigs";
            this->Button_AddFigs->UseVisualStyleBackColor = true;
            this->Button_AddFigs->Click += gcnew System::EventHandler(this, &Form1::Button_AddFigs_Click);
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 16;
            this->listBox1->Location = System::Drawing::Point(12, 89);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(120, 292);
            this->listBox1->TabIndex = 2;
            // 
            // openFileDialog1
            // 
            this->openFileDialog1->FileName = L"openFileDialog1";
            this->openFileDialog1->Filter = L"*.dll|*.dll";
            this->openFileDialog1->Multiselect = true;
            this->openFileDialog1->RestoreDirectory = true;
            // 
            // Button_DelSelFig
            // 
            this->Button_DelSelFig->Location = System::Drawing::Point(12, 50);
            this->Button_DelSelFig->Name = L"Button_DelSelFig";
            this->Button_DelSelFig->Size = System::Drawing::Size(78, 33);
            this->Button_DelSelFig->TabIndex = 3;
            this->Button_DelSelFig->Text = L"DelSelFig";
            this->Button_DelSelFig->UseVisualStyleBackColor = true;
            this->Button_DelSelFig->Click += gcnew System::EventHandler(this, &Form1::Button_DelSelFig_Click);
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(482, 405);
            this->Controls->Add(this->Button_DelSelFig);
            this->Controls->Add(this->listBox1);
            this->Controls->Add(this->Button_AddFigs);
            this->Controls->Add(this->pictureBox1);
            this->Name = L"Form1";
            this->Text = L"Render";
            this->ResizeEnd += gcnew System::EventHandler(this, &Form1::Form1_ResizeEnd);
            this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
        
        static System::String^ StdToSys(std::string StdStr)
        {
            return gcnew System::String(StdStr.c_str());
        }

        static const std::string SysToStd(System::String^ SysStr)
        {
            using namespace Runtime::InteropServices;
            char *v = (char*) (Marshal::StringToHGlobalAnsi(SysStr)).ToPointer() ;
            std::string result = std::string(v);
            Marshal::FreeHGlobal(System::IntPtr((void*)v));
            return result;
        }
               
        void RepaintScene()
        {
            listBox1->Items->Clear();  
            for( auto it = scene.m_shapes.begin(); it < scene.m_shapes.end(); ++it )
            {
                listBox1->Items->Add( StdToSys( it->m_shape_name.c_str() ));
            }
            scene.Refresh();
            for(int idx_y=0; idx_y < scene.Height(); idx_y++)
            {
                for(int idx_x=0; idx_x < scene.Width(); idx_x++)
                {
                    MyImage->SetPixel( idx_x, idx_y, Color::FromArgb( scene.m_scene[idx_x][idx_y].R, scene.m_scene[idx_x][idx_y].G, scene.m_scene[idx_x][idx_y].B ) );

                }
            }
            pictureBox1->Image = MyImage;
            pictureBox1->Refresh();
        }
        
private: System::Void Button_AddFigs_Click(System::Object^  sender, System::EventArgs^  e) 
         {
             if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
             {
                 for each ( String^ file in openFileDialog1->SafeFileNames ) 
                 {
                     String^ strfilename =  System::IO::Path::GetDirectoryName( openFileDialog1->FileName ) +"\\"+ file;
                     std::string name_dll = SysToStd( strfilename );
                     scene.LoadMyShape( name_dll );
                 }
             }
             RepaintScene();
         }

private: System::Void Button_DelSelFig_Click(System::Object^  sender, System::EventArgs^  e) 
         {
             std::vector< Geometr::MyShape > new_shapes_vector;
             int idx = 0;
             for( auto it = scene.m_shapes.begin(); it < scene.m_shapes.end(); ++it )
             {
                 if( listBox1->SelectedIndex != idx++ )
                     new_shapes_vector.push_back(*it);
             }
             scene.m_shapes.clear();
             scene.m_shapes = new_shapes_vector;
             listBox1->Items->Clear();
             for( auto it = scene.m_shapes.begin(); it < scene.m_shapes.end(); ++it )
             {
                 listBox1->Items->Add( StdToSys( it->m_shape_name.c_str() ));
             }
             RepaintScene();
         }

private: System::Void Form1_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
         {
             if((this->Height - 150)>(this->Width - 200))
             {
                 pictureBox1->Width = this->Width - 200;
                 pictureBox1->Height = pictureBox1->Width;
             }
             else if((this->Height - 150)<(this->Width - 200))
             {
                 pictureBox1->Height = this->Height - 150;
                 pictureBox1->Width = pictureBox1->Height;
             }
             else
             {
                 pictureBox1->Height = this->Height - 150;
                 pictureBox1->Width = this->Width - 200;
             }
         }


private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) 
         {
             if((this->Height - 150)>(this->Width - 200))
             {
                 pictureBox1->Width = this->Width - 200;
                 pictureBox1->Height = pictureBox1->Width;
             }
             else if((this->Height - 150)<(this->Width - 200))
             {
                 pictureBox1->Height = this->Height - 150;
                 pictureBox1->Width = pictureBox1->Height;
             }
             else
             {
                 pictureBox1->Height = this->Height - 150;
                 pictureBox1->Width = this->Width - 200;
             }
         }
};
}

