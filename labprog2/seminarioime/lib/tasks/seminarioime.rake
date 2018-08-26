namespace :seminarioime do
  desc "Limpa as presenças não usada."
  task attendences_collector: :environment do
  	Attendance.where(user_id: nil).destroy_all
  end
end
