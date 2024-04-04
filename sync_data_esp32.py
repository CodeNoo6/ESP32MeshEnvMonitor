
from tkinter import font
from tkinter import Toplevel, Entry

import psutil
import os
import tkinter as tk
from tkinter import ttk
from tkinter import filedialog
import csv
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import os
from tkinter import messagebox
import json



class FormularioArticulos:
    def __init__(self):
        self.paths=""
        self.ventana1 = tk.Tk()
        self.ventana1.title("Mantenimiento de artículos")
        self.title_font = font.Font(family='Arial', size=15, weight='bold')
        self.desc_font = font.Font(family='Arial', size=10)
        self.title_label = tk.Label(
            self.ventana1,
            text="MeshSync: Data Synchronization from the mesh network to Firestore",
            font=self.title_font,
            fg='blue',  # Color azul
        )
        self.title_label.grid(column=0, row=0, padx=15, pady=15)
        advertencia_text = "Attention! The ESP_ACTUAL folder is reserved for the device not to delete or modify"
        advertencia_label = tk.Label(self.ventana1, text=advertencia_text, bg="#FFFD66", fg="black", font=("Helvetica", 12, "bold"))
        advertencia_label.grid(column=0, row=1,pady=0)
        self.instrucciones_label = tk.Label(
            self.ventana1,
            text="Follow these instructions:\n1.Select from the list of storage devices the path that corresponds to the microSD card inserted in the device.\n2.Once selected, a list will be displayed with the names of the files contained on the microSD card.\n3.Verify and confirm that the following files contain the most recent records for mesh network synchronization.",
            font=self.desc_font,
            fg='black',  # Color azul
            justify='left'
        )
        self.instrucciones_label.grid(column=0, row=3, padx=25, pady=10)
        self.mensaje_carga = tk.Label(
            self.ventana1,
            text="0 datos sincronizados - 0%",
            font=self.desc_font,
            fg='black',  # Color azul
            justify='left'
        )
        self.mensaje_carga.grid(column=0, row=5, padx=25, pady=0)

        credentials_json = """
{
  "type": "service_account",
  "project_id": "bionic-freehold-415121",
  "private_key_id": "6dd69a3380c8546a0c122986152df69ddcff5e3b",
  "private_key": "-----BEGIN PRIVATE KEY-----\\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCQ4rapBcTHV9Y6\\n4P7/AYCH4BIiE4dPHRhMTrz6tH0c8VuCUMef1g6U4u8/AJJovfJHq6Hpu5cUb9gz\\ncQ6PO1nHRYmJ+sUrZ4N2cykY9L70nCh7yWqr11PKh2esNG3k44rCX++T8zYXl93A\\nfx9ciHg4B9HBSsrukvTdzjsSpg5V/yQfXTcyvO4LiiWic3mgokQJ7iO/uthtipuG\\nb2p3omcByYgfjuhytAn0WmQ3TElKerjjm3d0u2DlcMNTEsjAx3XnHzBTBEMbqZqf\\n/j+KvQ5c0URCdrvq6y46+cz+j8x8H7NhuyIcLEY6t4Aj+c/sqJ4E8hArE8wwd9UY\\nDlgWPqp9AgMBAAECggEAEoSXj2TdsL4o8x+SF+pg5iedHwkwmyD/MQmYnSZ3yJI5\\n/Z7w1MdZgm1ljL+NoaDdbYxMm9YjyjM9W93QXD2Gt7HLPCfMDu8iXf+mug+AtJJH\\nmQK2WpOhRwUlcAdyIEt2Ob+58Zv9Ruix1ApWFM/wevYs41qkM01JyhZeIH+5h1jC\\npeIejzt9lchd00dlPPy8VHsSBU7tk5zcg6t96/Ha86H4c1OO9HPYTyZcoRnPToJa\\nUReH9bBbNeSzFPP+EnKBYoBS9YmIXLwdSXw1hjYt4jTG5C/ZVw3PK9Lc+ZxWWaWr\\n21UIQNpFSiClP6BleUJOrAkyxszjlxYZ05+/rTZ5NQKBgQDDRvYB/a7dqKAdruSs\\ngQ1TN+6eA1uThFmo4H/INNqOmvuhu5QIsjaSUwnd5YW5NYYSQWyEzu8cFQull5yk\\nwdWywPNiy7aVhbJn1QFN5FPCVMX8fcLz/CnqYKE8vHQEt5jk0jU++866049Gu3Tf\\nbRXuyAj8EElbS1kkzo9phB8QUwKBgQC98FSSWbKWIPuLiG4ifhdmxiNOQ4z+cCav\\nak8P0tPcBglHq+SOEZkvNTSTvhXO//hDOJ2cwsgdi0aoDsMI2nIOymQn5TI3QCcJ\\ntYSmg9q7LLqspTslSxGjE2zSgLibXHN8fZYZD+1gZlqzoPfxO2+Z4oA+0hKrC622\\ncEMFR54/7wKBgEZB0qLWvcJcN/dWBEoYSE4Hkp9hP+JsPMHou7Cxa2zhT+VZkqIq\\nVD4DCErAmIMRQcJxrXR+60JkRAN478/LOXKNv0NtXaygJJb86PI4UvZY/76fFLQp\\npn7/8yLh/q/vyl+RTbzyZeeL1EGzkhIMslZtu+XMikgBbPo0Ix7ofTCnAoGAM76L\\na6tgCaJGpQav6lmrimYkLCge+xoWj+dITqlC6kgCszHS/BkzQDcgcbdxPYliWv3L\\ngm9WESZmQ1ZyL7FDLWBZ1LyN55tkhzKaRrrZFfDjkjEZYdmHnoOmO9qxcDHJjHqy\\nL3W1V3PK9fC+W0uz5ZpdEcAtMcfmtTL0LzYJmKUCgYEAg8RZIQcq0qGT4rjSi0Xz\\nxr7VDCbG3aRbXn3u3plxxGcd2TgKSCzh0gAmngbMc1kdyVWQMvywJjCkq3t0n4vd\\nL9UnGsEotAwoxQyueGKqtsw6lzAj4R7vHknRt07/SLQMzn7mb9nm8msvepdZi+wb\\nEwaKMRus7vUmwok7Qe9cEmY=\\n-----END PRIVATE KEY-----\\n",
  "client_email": "firebase-adminsdk-c5oww@bionic-freehold-415121.iam.gserviceaccount.com",
  "client_id": "117750392404742216265",
  "auth_uri": "https://accounts.google.com/o/oauth2/auth",
  "token_uri": "https://oauth2.googleapis.com/token",
  "auth_provider_x509_cert_url": "https://www.googleapis.com/oauth2/v1/certs",
  "client_x509_cert_url": "https://www.googleapis.com/robot/v1/metadata/x509/firebase-adminsdk-c5oww%40bionic-freehold-415121.iam.gserviceaccount.com",
  "universe_domain": "googleapis.com"
}
        """
        credentials_dict = json.loads(credentials_json)
        cred = credentials.Certificate(credentials_dict)
        firebase_admin.initialize_app(cred)
        self.db = firestore.client()
        self.carga_articulos()
        # Agregar la lógica de sincronización de datos
        self.actual = 0
        self.style = ttk.Style()
        self.style.configure("TProgressbar", troughcolor="green", background="green", lightcolor="green", darkcolor="green")
        self.progress = ttk.Progressbar(self.ventana1, orient="horizontal", length=810, mode="determinate", style="TProgressbar")
        self.progress.grid(row=6, column=0, padx=160,pady=20)

        self.button_font = font.Font(family='Verdana', size=7)

        # Crear una imagen para el botón (asegúrate de tener la imagen en la ruta correcta)
        self.image_path = "C:\\Users\\edwin\\Downloads\\cloud-service.png"
        self.original_image = tk.PhotoImage(file=self.image_path)
        self.resized_image = self.original_image.subsample(20)
        # Crear el botón con bordes redondeados y la imagen ajustada
        self.button_submit = tk.Button(
            self.ventana1,
            text="SYNC DATA NOW",
            font=self.button_font,
            bg='#FFFD66',
            fg='#363621',
            bd=0,
            height=30,
            width=800,
            command=self.sincronizar_datos,
            relief="ridge",
            image=self.resized_image,
            compound="right"
        )
        self.button_submit.grid(row=4, column=0, padx=0,pady=15)
        self.button_submit.config(state=tk.DISABLED)


        self.desc_label = tk.Label(
            self.ventana1,
            text="The desktop application aims to automate the process of uploading environmental data transmitted through a mesh network.\n This data is stored in comma-separated files on the microSD card of each node in the network.",
            font=self.desc_font,
            fg='black',  # Color azul
            justify='center'
        )
        self.desc_label.grid(column=0, row=2, padx=10, pady=0)

        self.ventana1.mainloop()

    def pop_up_upload_succesful(self):
        # Crear la ventana principal
        ventana_principal = Toplevel(self.ventana1)

        # ... (El código para la ventana principal)

        # Agregar el código para la tabla y las entradas como lo hiciste anteriormente
        for r in range(0, 3):
            for c in range(0, 2):
                cell = Entry(ventana_principal, width=30, fg='#CFCFDC', bg='black', justify='center',
                             font=('Helvetica', 12, 'bold'))
                cell.grid(padx=15, pady=0, row=r + 1, column=c)
                cell.insert(0, '({}, {})'.format(2, 2))
                cell.configure(state='readonly')





    def sincronizar_datos(self):
        """
        self.actual += 33
        # Acción a realizar al hacer clic en el botón
        self.progress["value"] = self.actual
        if self.actual < 50:
            self.style.configure("TProgressbar", troughcolor="green", background="green", lightcolor="green", darkcolor="green")
        else:
            self.style.configure("TProgressbar", troughcolor="red", background="red", lightcolor="red", darkcolor="red")
        self.ventana1.after(1000, self.sincronizar_datos)
        print(self.paths)
        """
        for elem in os.listdir(self.paths):
            print("Elemento")
            print(elem)
            ruta_completa=os.path.join(self.paths, elem)
            print(ruta_completa)
            dispositivo = []
            if (os.path.isdir(ruta_completa) and ruta_completa not in [r"D:\ESP_ACTUAL", r"D:\System Volume Information"]):
                for archivo in os.listdir(ruta_completa):
                    print("Archivo")
                    ruta=os.path.join(ruta_completa, archivo)
                    print(archivo)
                    if archivo.endswith('.csv'):
                        id=archivo.find("_")
                        print("id")
                        print(id)
                        if(id!=-1):
                            print("Dispositivos")
                            num_data=1
                            dispositivo.append(archivo[id+ 1:-4])
                            print(dispositivo)
                        try:
                            with (open(ruta,'r',encoding='latin-1') as file):
                                csv_reader = csv.reader(file)
                                print("csv_reader")
                                print(csv_reader)
                                line_count =0
                                for linea in file:
                                    line_count=line_count+1
                                file.seek(0)
                                print("line")
                                print(line_count)
                                for line in csv_reader:
                                    print(line)
                                    segmentos = line[0].strip().rstrip(';').split(';')
                                    valores = {}
                                    print("lineeeeeee")
                                    for segmento in segmentos:
                                        print(segmento)
                                        if('Fecha y hora de muestra' in segmento):
                                            clave_valor = [clave_valor for clave_valor in segmento.strip().split(':',1)]
                                        else:
                                            clave_valor = [clave_valor for clave_valor in segmento.strip().split(':')]
                                        pos_particulas = 0
                                        if ("Particulas" in clave_valor[0]):
                                            pos_particulas += 1

                                        if "PM entorno 1.0" in clave_valor[0]:
                                            clave_valor[0]="PMEnvironment 1.0"
                                        if "PM entorno 2.5" in clave_valor[0]:
                                            clave_valor[0]="PM10Environment2.5"
                                        valores[clave_valor[pos_particulas]] = clave_valor[1 + pos_particulas] if len(clave_valor) > 1 + pos_particulas else ""
                                        dict_pm = [(key, valores[key]) for key in valores.keys() if key.startswith("PM")]
                                        valores_pm = {key: v for key,v in dict_pm}
                                    datos = {
                                        "DS3231": valores.get("Fecha y hora de muestra", ""),
                                        "DHT": {
                                            "Humidity": valores.get("Humedad", ""),
                                            "Temperature": valores.get("Temperatura", "")
                                        },
                                        "GPS": {
                                            "Latitude": valores.get("Latitud", ""),
                                            "Longitude": valores.get("Longitud", ""),
                                            "Speed": valores.get("Velocidad", ""),
                                            "Satellites": valores.get("Satelites", "")
                                        },
                                        "PM": valores_pm
                                    }
                                    print("Ventana")
                                    count = len(list(self.db.collection("device-"+dispositivo[0]).get()))  ##Retorna el numero del ultimo registro
                                    print("cantidad")
                                    print(count)
                                    print("device-"+dispositivo[0])
                                    self.db.collection("device-"+dispositivo[0]).document(f"Registro-{count + 1}").set(datos)
                                    print("---------------------entra")
                                    num_data=num_data+1
                                    v_prog=round(((num_data)*100)/line_count,0)
                                    if (v_prog > 100):
                                        v_prog = 100
                                    self.progress["value"]=v_prog
                                    msg="Novedad: Nodo: "+dispositivo[0]+" ha subido " + str(num_data) + " registros \n Progreso: "+str(v_prog)+"%"
                                    print(msg)
                                    self.mensaje_carga.config(text=msg)
                                    self.ventana1.update_idletasks()
                            carpeta_contenedora = os.path.dirname(ruta)
                            os.remove(ruta)
                            os.rmdir(carpeta_contenedora)
                            messagebox.showinfo("Información", "Datos insertados correctamente desde el archivo CSV.")
                        except Exception as e:
                            messagebox.showerror("Error", f"Error al insertar datos desde el archivo CSV: {e}")
                            msg = "Hubo un problema al cargar el registro"
                            self.mensaje_carga.config(text=msg)

    def list_devices(self):
        datos = []
        dispositivos = psutil.disk_partitions(all=True)
        print("Dispositivos y unidades de almacenamiento:")
        for dispositivo in dispositivos:
            print("Nombre del dispositivo:", dispositivo.device)
            statistics = psutil.disk_usage(dispositivo.mountpoint)
            print(f"Total: {statistics.total} bytes")
            print(f"Usado: {statistics.used} bytes")
            print(f"Libre: {statistics.free} bytes")
            statistic_data = (dispositivo.device, round(int(statistics.total)/(1024**2),2), round(int(statistics.used)/(1024**2),2),round(int(statistics.free)/(1024**2)),2)
            datos.append(statistic_data)
            print("-----------------DATOS-------------------")
            print(datos)
        return datos

    def obtener_valor_seleccionado(self,event):
        celda_seleccionada = self.treeview.selection()
        if celda_seleccionada:
            item = self.treeview.item(celda_seleccionada)
            valores_fila = item['values']
            print("Fila seleccionada:", valores_fila[0])
        else:
            print("Ninguna fila seleccionada")
        self.paths=valores_fila[0]
        self.listbox.delete(0, tk.END)
        # Add elements to the Listbox
        elements = ["Element 1", "Element 2", "Element 3", "Element 4","Element 4","Element 4"]
        for element in self.list_folder_files(valores_fila[0]):
            self.listbox.insert(tk.END, element)
        # Suponiendo que self.listbox es tu Listbox...
        self.button_submit.config(state=tk.NORMAL)

    def carga_articulos(self):
        self.cuaderno1 = ttk.Notebook(self.ventana1)
        self.pagina1 = ttk.Frame(self.cuaderno1)
        self.labelframe1 = ttk.LabelFrame(self.pagina1, text="Tabla de dispositivos")
        self.labelframe1.grid(column=0, row=0, padx=0, pady=20)  # Ajuste de pady
        self.listbox = tk.Listbox(self.labelframe1, selectmode=tk.SINGLE, height=25, width=133)
        self.listbox.grid(row=2, column=0, padx=0, pady=0)
        self.cuaderno1.add(self.pagina1, text="Sincronizar datos a la nube")
        self.cuaderno1.grid(column=0, row=7,padx=0,pady=0)  # Ajuste de pady

        self.headers = {
            "table": [{'1': 'Storage device name', '2': 'Total Space MB', '3': 'Used space MB', '4': 'Free Space MB'}]
        }
        indexs = [list(x[0]) for x in self.headers['table'][0].items()]
        print("--------------------Indices------------------------")
        print(indexs)
        self.treeview = ttk.Treeview(self.labelframe1, columns=(indexs[0], indexs[1], indexs[2], indexs[3]),
                                     show='headings')
        for num, name_column in self.headers['table'][0].items():
            self.treeview.heading(num, text=name_column)
        for dato in self.list_devices():
            self.treeview.insert('', 'end', values=dato)

        self.treeview.grid(row=1, column=0, pady=25)
        self.treeview.bind('<<TreeviewSelect>>', self.obtener_valor_seleccionado)

        style = ttk.Style()
        style.configure("Treeview", rowheight=12)

    def list_folder_files(self, path_route):
        lista=[]
        for elem in os.listdir(path_route):
                lista.append(os.path.join(path_route, elem))
        return lista

# Crear una instancia de la clase FormularioArticulos
aplicacion1 = FormularioArticulos()
