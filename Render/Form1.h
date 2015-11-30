#pragma once

namespace Render {
   
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace Scene;
	/// <summary>
	/// Summary for Form1
	/// </summary>
	 MyScene scene;

	public ref class Form1 : public System::Windows::Forms::Form
	{
   
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::PictureBox^  pictureBox1;
    protected: 
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::ListBox^  listBox1;
    private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
                    
        

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
            this->SuspendLayout();
            // 
            // pictureBox1
            // 
            this->pictureBox1->Location = System::Drawing::Point(160, 89);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(300, 300);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(13, 39);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(75, 23);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Scene";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 16;
            this->listBox1->Location = System::Drawing::Point(13, 89);
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
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(508, 414);
            this->Controls->Add(this->listBox1);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->pictureBox1);
            this->Name = L"Form1";
            this->Text = L"Render";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
        bool isLineDot(int x, int y, int x1, int y1, int x2, int y2)
        {
            if(x<x1 || x>x2 || y<y1 || y>y2)
                return false;
            double line_ = ((double)y1 - (double)y2)*(double)x + ((double)x2 - (double)x1)*(double)y+ ((double)x1 * (double)y2 - (double)x2 * (double)y1);
            if(line_ < 2 && line_>-2 )
                return true;
            return false;
        };

        static System::String^ StdToSys(std::string StdStr){
            return gcnew System::String(StdStr.c_str());
        }
        static const std::string SysToStd(System::String^ SysStr){
            using namespace Runtime::InteropServices;
            char *v = (char*) (Marshal::StringToHGlobalAnsi(SysStr)).ToPointer() ;
            std::string result = std::string(v);
            Marshal::FreeHGlobal(System::IntPtr((void*)v));
            return result;
        }
        wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
        {
            wchar_t* wString=new wchar_t[4096];
            MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
            return wString;
        }

    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                //MyScene scene;
                LPCWSTR name_dll;
                if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
                {
                    for each ( String^ file in openFileDialog1->SafeFileNames ) 
                    {
                       // MultiByteToWideChar(NULL, NULL, SysToStd( file ).c_str(), 10, name_dll, 10);
                        String^ strfilename =  System::IO::Path::GetDirectoryName( openFileDialog1->FileName ) +"\\"+ file;
                        std::string _str = SysToStd(strfilename);
                        ;
                        name_dll = (LPCWSTR)convertCharArrayToLPCWSTR( _str.c_str() );
                        scene.LoadMyShape( name_dll );
                    }
                }
                /*
                std::string patch_file_name = SysToStd( openFileDialog1->InitialDirectory );

                std::vector<std::string> dll_file_vector;
                HANDLE hFind;
                WIN32_FIND_DATA FindFileData;

                if((hFind = FindFirstFile((LPCWSTR)patch_file_name.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE){
                    do{
                        dll_file_vector.push_back( FindFileData.cFileName );
                    }while(FindNextFile(hFind, &FindFileData));
                    FindClose(hFind);
                }
                for(auto it_dll_file_vector = dll_file_vector.begin(); it_dll_file_vector != dll_file_vector.end(); ++it_dll_file_vector )
                {
                    name_dll = *it_dll_file_vector;
                    scene.LoadMyShape( name_dll );
                }*/

                /***
                name_dll = ( L"f:\\1\\geometr\\Figs\\fig_triangle2.dll" );
                scene.LoadMyShape( name_dll );
                name_dll = ( L"f:\\1\\geometr\\Figs\\fig_triangle3.dll" );
                scene.LoadMyShape( name_dll );
                *///
                scene.CalcScene();                
                pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
                Bitmap ^MyImage = gcnew Bitmap(500,500);
                pictureBox1->Image = MyImage;
                int x=0;
                for( auto it = scene.m_shapes.begin(); it < scene.m_shapes.end(); ++it )
                {
                    //String ^ Item = it->m_shape_name.c_str();
                    //listBox1->Items->Add( it->m_shape_name.c_str() );
                     
                     listBox1->Items->Add( StdToSys( it->m_shape_name.c_str() ));
                    //listBox1->it add( it->m_shape_name );
                }
                                        
                    for(int idx_y=0; idx_y<500; idx_y++)
                    {
                        for(int idx_x=0; idx_x<500; idx_x++)
                        {
                             MyImage->SetPixel( idx_x, idx_y, Color::FromArgb( scene.m_scene[idx_x][idx_y].R, scene.m_scene[idx_x][idx_y].G, scene.m_scene[idx_x][idx_y].B ) );
                          /*
                            MyImage->GetPixel( idx_x, idx_y );
                            if( it->IsDotPoligon(idx_x, idx_y) )
                                MyImage->SetPixel(  idx_x,idx_y, Color::FromArgb( it->m_color_lines.R, it->m_color_lines.G, it->m_color_brush.B ));

                            if( it->IsDotLine(idx_x, idx_y) )
                                MyImage->SetPixel(idx_x,idx_y, Color::FromArgb( it->m_color_lines.R, it->m_color_lines.G, it->m_color_lines.B ));
                            */
                           
                        }
                    }
                
                pictureBox1->Refresh();
                
                //scene.LoadMyShape( );
             }
    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
                 openFileDialog1->ShowDialog();
             }
};
}

