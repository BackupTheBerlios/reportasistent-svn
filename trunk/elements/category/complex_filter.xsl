<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="attr_name" label="Attribute name" />
            <attribute name="ctgr_name" label="Category name"/>
            <attribute name="ctgr_type" label="Type of category"/>
            <attribute name="ctgr_freq" label="Frequency"/>
            <attribute name="bool_type" label="Boolean type"/>
            <attribute name="def_length" label="Definition length"/>
            <attribute name="category_definition" label="Category definition"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="attr_name" label="Jméno atributu" />
            <attribute name="ctgr_name" label="Název kategorie"/>
            <attribute name="ctgr_type" label="Typ kategorie"/>
            <attribute name="ctgr_freq" label="Frekvence"/>
            <attribute name="bool_type" label="Booleovský typ"/>
            <attribute name="def_length" label="Délka definice"/>
            <attribute name="category_definition" label="Definice kategorie"/>
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->
      </attributes>

      <values>
        <xsl:apply-templates select="category" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>







  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<xsl:text disable-output-escaping="yes">category_definition="</xsl:text>
		<xsl:apply-templates select="ctgr_def" mode="values"/>
		<xsl:text disable-output-escaping="yes">"</xsl:text>

		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu pro ctgr_def -->
	<xsl:template match="ctgr_def" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@definition"/>
	</xsl:template>





	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
