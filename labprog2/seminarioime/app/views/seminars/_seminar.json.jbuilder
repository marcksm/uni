json.extract! seminar, :id, :seminar_id, :name, :description, :place, :date, :created_at, :updated_at
json.url seminar_url(seminar, format: :json)
