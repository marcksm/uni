class CreateProfessors < ActiveRecord::Migration[5.1]
  def change
    create_table :professors do |t|
      t.string :email
      t.string :token
      t.boolean :register
      t.boolean :usertype
      t.timestamps
    end
  end
end
